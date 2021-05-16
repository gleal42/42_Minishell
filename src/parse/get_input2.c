/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 10:11:09 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/16 01:15:52 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_input.h"

/*
** Execute the expected bahaviour after Ctrl-C, which is to write "^C" to
** stdout and reset the command line
** @param:	- [char *] buffer where input chars and ctrl-c have been stored
**			- [int *] size of the buffer before last read. We pass pointer
**					  because we need to set it to 0
**			- [t_dlist **] reference to input_history
** Line-by-line comments:
** @6-10	After pressing Ctrl-C, we need to rewind the input history
*/

void	reset_cmd_line(char *buf, int *i, t_dlist **input_history)
{
	write(STDOUT_FILENO, "^C\n", ft_strlen("^C\n"));
	g_msh.exit_status = EXIT_CMD_INTERRUPTED;
	write_prompt();
	ft_bzero(buf, BUFSIZ);
	*i = 0;
	if (*input_history)
	{
		while ((*input_history)->prev)
			*input_history = (*input_history)->prev;
	}
}

/*
** Execute the expected behaviour after Ctrl-D, which to write "exit" and to
** exit the shell
** @param:	- [char *] buffer where input chars and ctrl-d have been stored
**			- [int] size of the buffer before last read
** Line-by-line comments:
** @1		Ctrl-D only exits the program if the cmd line was previously empty
** @3		We need to overwrite the End of Transmission character from the
**			buffer if we don't exit
*/

void	exit_program(char *buf, int i)
{
	if (i > 0)
	{
		buf[i] = '\0';
		return ;
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	quit_program(g_msh.exit_status);
}

/*
** Extract the input from the buffer
** @param:	- [char *] buffer where characters were inputed
**			- [int] buffer size
** @return:	[char *] input without the line feed
** Line-by-line comments:
** @3		Deleting the line feed from the buffer
*/

char	*extract_input(char *buf, int i)
{
	char	*input;

	buf[i - 1] = '\0';
	input = ft_strdup(buf);
	if (!input)
		quit_program(EXIT_FAILURE);
	return (input);
}
