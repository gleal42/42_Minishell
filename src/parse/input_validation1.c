/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:06:43 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/03 10:39:53 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_validation.h"

/*
** Checks if input entered in cmd line is valid while displaying error messsage
** @param:	- [const char *] the unchanged line entered in stdin
** @return:	[int] true or false
*/

int	is_input_valid(const char *input)
{
	int		check;
	char	err_message[100];

	if (*input == '\0' || ft_strisspace((char *)input))
		check = 0;
	else if (!is_input_valid_unpected_token(input, err_message)
		|| !is_input_valid_not_supported(input, err_message))
	{
		check = 0;
		errno = 2;
		write_gen_err_message(err_message);
	}
	else
		check = 1;
	return (check);
}

int	is_input_valid_unpected_token(const char *input, char *err_message)
{
	int		check;

	if (has_quotes_open(input, err_message)
		|| has_char_at_beginning(input, '|', err_message)
		|| has_char_at_beginning(input, ';', err_message)
		|| has_char_at_end(input, '|', err_message)
		|| has_char_at_end(input, '<', err_message)
		|| has_char_at_end(input, '>', err_message)
		|| has_char_at_end(input, '&', err_message)
		|| has_str(input, ";;", err_message)
		|| has_str(input, ";|", err_message)
		|| has_str(input, ";&", err_message)
		|| has_str(input, ";;", err_message)
		|| has_str(input, ">>>", err_message)
		|| has_spaces_between_char(input, '|', err_message)
		|| has_spaces_between_char(input, '>', err_message))
		check = 0;
	else
		check = 1;
	return (check);
}

int	is_input_valid_not_supported(const char *input, char *err_message)
{
	int		check;

	if (has_non_supported(input, "<<", err_message)
		|| has_non_supported(input, "*", err_message)
		|| has_non_supported(input, "&&", err_message)
		|| has_non_supported(input, "&", err_message)
		|| has_non_supported(input, "||", err_message)
		|| has_non_supported(input, "|", err_message))
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
** @param:	- [const char *] the unchanged line entered in stdin
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

int	has_quotes_open(const char *input, char *err_message)
{
	int	check;
	int	has_double_quotes_open;
	int	has_single_quotes_open;

	check = 1;
	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (*input)
	{
		if (*input == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (*input == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		input++;
	}
	if (has_double_quotes_open || has_single_quotes_open)
	{
		check = 1;
		ft_strcpy(err_message, "syntax error: open quotes");
	}
	else
		check = 0;
	return (check);
}

/*
** Checks if there is a specific character at beginning of input
** @param:	- [const char *] the unchanged line entered in stdin
** @return:	[int] true or false
** Line-by-line comments:
** @5-8		We need to trim white space from the input while
**			not changing the initial input
*/

int	has_char_at_beginning(const char *input, char c, char *err_message)
{
	int		check;
	char	*cpy;

	cpy = ft_strtrim(input, " \t\n\v\f\r");
	if (!cpy)
		ft_exit(EXIT_FAILURE);
	if (cpy[0] == c)
	{
		check = 1;
		ft_strcpy(err_message, "syntax error near unexpected token `");
		ft_strncat(err_message, &c, 1);
		ft_strncat(err_message, "'", 2);
	}
	else
		check = 0;
	free(cpy);
	return (check);
}
