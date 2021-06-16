/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 20:16:20 by gleal             #+#    #+#             */
/*   Updated: 2021/05/24 17:10:26 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_echo.h"

/*
** Prints args to standard output separated by spaces
** @param:	- [t_list *] arguments/tokens
** @return:	[int] exit_status
** Line-by-line comments:
** @12-18	There can be multiple flag arguments, but as soon as we get a non
**			flag argument then flag time is over
*/

int	ft_echo(t_list *tokens)
{
	int		line_break;
	int		flag_time;
	char	*arg;

	flag_time = 1;
	line_break = 1;
	while (tokens)
	{
		arg = tokens->data;
		if (flag_time && arg[0] == '-' && has_repeated_char_in_str('n', arg, 1))
			line_break = 0;
		else
		{
			if (!flag_time)
				ft_putchar_fd(' ', STDOUT_FILENO);
			flag_time = 0;
			ft_putstr_fd(arg, STDOUT_FILENO);
		}
		tokens = tokens->next;
	}
	if (line_break)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

/*
** Function to look for repeated characters
** @param:	- [char] char to be checked
**			- [char *] string to be parsed
**			- [unsigned int] iterator start
** @return:	[int] true or false
*/

int	has_repeated_char_in_str(char repeat_chr, char *str, unsigned int start)
{
	unsigned int	i;

	i = start;
	while (str[i])
	{
		if (str[i] != repeat_chr)
			return (0);
		i++;
	}
	return (1);
}
