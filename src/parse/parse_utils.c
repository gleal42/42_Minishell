/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:26:41 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/03 10:42:41 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

/*
** Skips all spaces starting at curr_pos while incrementing *curr_pos
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
*/

void	skip_spaces(const char *input, int *curr_pos)
{
	while (ft_isspace(input[*curr_pos]))
		(*curr_pos)++;
}

/*
** Checks if the char is a cmd delimiter
** @param:	- [char] the characters
** @return:	[int] true or false
** Line-by-line comments:
** @9-10	& isn't supposed to be a delimiter. But "&&" is. If '&' is on its
**			own, the function is_input_valid() will flag that
*/

int	is_delimiter(char c)
{
	int	check;

	if (c == ' ')
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
** Gets the delimiter that is enclosing the token starting
** at input[*curr_pos]
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
** @return:	[char] delimiter. Space, single quotes or double quotes
** Line-by-line comments:
** @9		We need to increment once if we found quotes so that the token
**			starts after the quote
*/

char	get_delimiter(const char *input, int *curr_pos)
{
	char	delimiter;

	delimiter = 0;
	if (input[*curr_pos] == '"' || input[*curr_pos] == '\'')
	{
		if (input[*curr_pos] == '"')
			delimiter = '"';
		else if (input[*curr_pos] == '\'')
			delimiter = '\'';
		(*curr_pos)++;
	}
	else
		delimiter = ' ';
	return (delimiter);
}

void	skip_quotes(char *str, int *i)
{
	int		has_double_quotes_open;
	int		has_single_quotes_open;

	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (str[*i])
	{
		if (str[*i] == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (str[*i] == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		else if (!has_double_quotes_open && !has_single_quotes_open)
			break ;
		(*i)++;
	}
}

char	*ft_strstr_quotes(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (!(*to_find))
		return (str);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes(str, &i);
		if (!ft_strncmp(&str[i], to_find, ft_strlen(to_find)))
			return (&str[i]);
		i++;
	}
	return (0);
}
