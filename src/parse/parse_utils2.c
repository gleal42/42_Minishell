/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 08:34:51 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 11:12:36 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

/*
** Checks if the string is a command table delimiter
** @param:	- [const char *] the piece of string tested
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
** Checks if the char is a token delimiter
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

/*
** Gets the cmd_table_delimiter and increments the according amount of
** characters in curr_pos
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
** @return:	[char *] the delimiter. Can be "\0", ";", "||" or "&&"
** Line-by-line comments:
** @14		We need to increment by the amount of the delimiter. Can be 0, 1
**			or 2
*/

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

/*
** Checks if it's a supported ctrl <letter> combinaision. All ctrl + <letter>
** have an ASCII value between 0 and 31
** @param:	- [char] inputed character
**			- [type] param_value
** @return:	[int] true or false
** Line-by-line comments:
** @3-4		Ctrl-c (ie 3), ctrl-d (ie 4) and enter keypcap (ie 10) are all valid
*/

int	is_ctrl(char c)
{
	int	check;

	if (c == CTRL_C || c == CTRL_D || c == ENTER_KEYCAP)
		check = 0;
	else if ((0 <= c && c <= 31) || c == 127)
		check = 1;
	else
		check = 0;
	return (check);
}
