/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 08:34:51 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/17 19:00:21 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

/*
** Checks if the char is a command delimiter
** @param:	- [char] the character tested
** @return:	[int] true or false
*/

int	is_cmd_table_delimiter(const char *str)
{
	int	check;

	if (*str == ';')
		check = 1;
	else if (!ft_strncmp((char *)str, "||", 2))
		check = 1;
	else if (!ft_strncmp((char *)str, "&&", 2))
		check = 1;
	else
		check = 0;
	return (check);
}

/*
** Checks if the char is a command delimiter
** @param:	- [char] the character tested
** @return:	[int] true or false
*/

int	is_cmd_delimiter(char c)
{
	int	check;

	if (c == ';')
		check = 1;
	else if (c == '|')
		check = 1;
	else if (c == '&')
		check = 1;
	else
		check = 0;
	return (check);
}

/*
** Checks if the char is a command delimiter
** @param:	- [char] the character tested
** @return:	[int] true or false
*/

int	is_token_delimiter(char c)
{
	int	check;

	if (ft_strchr(WHITE_SPACE, c) != 0)
		check = 1;
	else if (c == ';')
		check = 1;
	else if (c == '|')
		check = 1;
	else if (c == '&')
		check = 1;
	else if (c == '<')
		check = 1;
	else if (c == '>')
		check = 1;
	else
		check = 0;
	return (check);
}

char	*get_cmd_table_delimiter(const char *input, int *curr_pos)
{
	char	*delimiter;

	delimiter = 0;
	if (input[*curr_pos] == '\0')
		delimiter = ft_strdup("");
	else if (input[*curr_pos] == ';')
		delimiter = ft_strdup(";");
	else if (!ft_strncmp((char *)&input[*curr_pos], "||", 2))
		delimiter = ft_strdup("||");
	else if (!ft_strncmp((char *)&input[*curr_pos], "&&", 2))
		delimiter = ft_strdup("&&");
	if (!delimiter)
		quit_program(EXIT_FAILURE);
	(*curr_pos) += ft_strlen(delimiter);
	return (delimiter);
}
