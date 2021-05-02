/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 10:11:09 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/02 10:37:09 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_input.h"

void	reset_cmd_line(char *buf, int *i)
{
	write(STDOUT_FILENO, "^C\n", ft_strlen("^C\n"));
	write_prompt();
	ft_bzero(buf, BUFSIZ);
	*i = 0;
}

void	exit_program(char *buf, int i)
{
	if (ft_strlen(buf) != 1)
	{
		buf[i] = '\0';
		return ;
	}
	write(STDOUT_FILENO, "exit\n", ft_strlen("exit\n"));
	ft_exit(EXIT_SUCCESS);
}

char	*extract_input(char *buf, int i)
{
	char	*input;

	buf[i - 1] = '\0';
	input = ft_strdup(buf);
	if (!input)
		ft_exit(EXIT_FAILURE);
	return (input);
}
