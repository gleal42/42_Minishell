/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:26:41 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 11:06:08 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

/*
** Same function as strstr but it will only look for the string to_find outside
** of quotes (single or double)
** @param:	- [char *] string where we are looking (aka the haystack)
**			- [char *] string to find (aka the needle)
** @return:	[char *] address where the needle is
** Line-by-line comments:
** @8-9		If we find a single or double quote, we need to skip them. The next
**			character will be the one after the closing matching quote
** @10-11	The exact next character after skip_quotes() can be a string to_find
**			so we can't use else if pattern
** @12-13	skip_quotes() can reach end of string so we need check for that
**			before incrementing otherwise we'll segfault
*/

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
		if (str[i])
			i++;
	}
	return (0);
}

/*
** Parses a string until the index i no longer points to a character inside
** quotes (single or double)
** @param:	- [const char *] string to parse
**			- [int *] index of the string. We have the reference because
**					  we need to update its value for the function caller
** Line-by-line comments:
** @8-9		If we find a double quotes and single quotes are not open,
**			we set has_double_quotes_open to its opposite, meaning:
**			- true if it was initially false (we are opening double quotes)
**			- false if it was initially true (we are closing double quotes)
**			We don't care about double quotes if single quotes are open because
**			it will all be part of the token enclosed by the single quotes
** @10-11	Exact same logic as for the double quotes
*/

void	skip_quotes(const char *input, int *curr_pos)
{
	int		has_double_quotes_open;
	int		has_single_quotes_open;

	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (input[*curr_pos])
	{
		if (input[*curr_pos] == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (input[*curr_pos] == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		(*curr_pos)++;
		if (!has_double_quotes_open && !has_single_quotes_open)
			break ;
	}
}

/*
** Skips all spaces starting at curr_pos while incrementing *curr_pos
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
*/

void	skip_spaces(const char *input, int *curr_pos)
{
	while (input[*curr_pos] && ft_isspace(input[*curr_pos]))
		(*curr_pos)++;
}

/*
** Skips all letters. Considers $PATH in $PATH$TERM as it's own string.
** Same for /bin in /bin/ls
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
** Line-by-line comments:
** @1-2		If first character is $ or / then we are in the case of an
** 			environment variable or an absolute path
*/

void	skip_letters(const char *input, int *curr_pos)
{
	if (input[*curr_pos] == '$' || input[*curr_pos] == '/')
		(*curr_pos)++;
	while (input[*curr_pos] && !is_quote(input[*curr_pos])
		&& input[*curr_pos] != '$' && input[*curr_pos] != '/')
		(*curr_pos)++;
}

/*
** Deletes the useless quotes from a token. What is useless? Too hard to explain
** here are 2 examples:
** - Level 0:
** $ echo h"42"
** h42
** - Level can't-wait-to-done-with-minishell:
** $ echo hello"wor'ld"'te"st'
** hellowor'ldte"st
** @param:	- [char *] the token extracted from the input
** Line-by-line comments:
** @8-23	We are parsing the token to look for matching quotes within the
** 			token. Each time we find a matching quote (either the first time
**			or the second), we overwrite it by offsetting the rest of the string
**			by 1 to the left 
** @10-15	We only can overwrite a double quote if we currently have not single
**			quotes open
** @12		We set the boolean has_double_quotes_open to its opposite current
**			value each time we find a double quotes
** @14		Each time we offset by one, we need to continue to skip the
**			incrementation at the bottom of the loop statement
*/

void	delete_quotes(char *token)
{
	int	i;
	int	has_double_quotes_open;
	int	has_single_quotes_open;

	i = 0;
	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (token[i])
	{
		if (token[i] == '"' && has_single_quotes_open == 0)
		{
			has_double_quotes_open = !has_double_quotes_open;
			ft_strcpy(&token[i], (const char *)&token[i + 1]);
			continue ;
		}
		else if (token[i] == '\'' && has_double_quotes_open == 0)
		{
			has_single_quotes_open = !has_single_quotes_open;
			ft_strcpy(&token[i], (const char *)&token[i + 1]);
			continue ;
		}
		i++;
	}
}
