/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:06:43 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/23 17:29:24 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_validation.h"

/*
** Checks if input entered in cmd line is valid while displaying error messsage
** @param:	- [const char *] input entered in cmd line
** @return:	[int] true or false
*/

int	is_input_valid(const char *raw_input)
{
	int	check;

	if (has_quotes_open(raw_input))
	{
		write_gen_err_message("syntax error (open quotes)");
		check = 0;
	}
	else if (has_pipe_at_end(raw_input))
	{
		write_gen_err_message("syntax error near unexpected "
							"token `|'");
		check = 0;
	}
	else if (*raw_input == '\0' && ft_strisspace((char *)raw_input))
		check = 0;
	else
		check = 1;
	return (check);
}

/*
** Checks if the input has any open quotes (single or double).
** Considered as open quotes:
** - "
** - " '
** - " ' " '
** Not considered as open quotes:
** - " "
** - " ' "
** - " ' ' "
** @param:	- [char *] the unchanged line entered in stdin
** @return:	[int] true or false
** Line-by-line comments:
** @10-11	If we find a double quotes and single quotes are not open,
**			we set has_double_quotes_open to its opposite, meaning:
**			- true if it was initially false (we are opening double quotes)
**			- false if it was initially true (we are closing double quotes)
**			We don't care about double quotes if single quotes are open because
**			it will all be part of the token enclosed by the single quotes
** @12-13	Exact same logic as for the double quotes
*/

static int	has_quotes_open(const char *raw_input)
{
	int	check;
	int	has_double_quotes_open;
	int	has_single_quotes_open;

	check = 1;
	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (*raw_input)
	{
		if (*raw_input == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (*raw_input == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		raw_input++;
	}
	if (has_double_quotes_open || has_single_quotes_open)
		check = 1;
	else
		check = 0;
	return (check);
}

/*
** Checks if there is a pipe at the end of input
** @param:	- [const char *] input entered in cmd line
** @return:	[int] true or false
** Line-by-line comments:
** @5-8		We need to trim white space from the input while
**			not changing the initial input
*/

static int	has_pipe_at_end(const char *raw_input)
{
	int		check;
	char	*cpy;
	int		len;

	cpy = ft_strdup(raw_input);
	if (!cpy)
		exit(EXIT_FAILURE);
	cpy = ft_strtrim(cpy, " \t");
	len = ft_strlen(cpy);
	if (cpy[len - 1] == '|')
		check = 1;
	else
		check = 0;
	free(cpy);
	return (check);
}
