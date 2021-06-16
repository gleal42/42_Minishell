/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:06:43 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/18 15:51:39 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_validation.h"

/*
** Checks if input entered in cmd line is valid while displaying error messsage
** @param:	- [const char *] the unchanged line entered in stdin
** @return:	[int] true or false
** @5-6		Case: empty or only white space. It doesn't require an error message
** @11		Some testers say that the errno needs to be 2 but not very
**			consistent across different OS. So we choose to set it to
**			ENOEXEC (Exec format error), which value will adapt across OS
*/

int	is_input_valid(const char *input)
{
	int		check;
	char	err_message[100];

	ft_bzero(err_message, 0);
	if (*input == '\0' || ft_strisspace((char *)input))
		check = 0;
	else if (!is_input_valid_unexpected_token(input, err_message)
		|| !is_input_valid_not_supported(input, err_message))
	{
		check = 0;
		g_msh.exit_status = ENOEXEC;
		write_msh_error(err_message);
	}
	else
		check = 1;
	return (check);
}

/*
** Checks if the input has an unexpected token
** @param:	- [const char *] the unchanged line entered in stdin
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
** Line-by-line comments:
** @4-9		has_char_at_beginning() and has_char_at_end() trim whitespaces at
**			both ends of the input before checking
** @10-15	The has_forbidden_sequence() function remove all white spaces
** 			(except between quotes) before checking
*/

int	is_input_valid_unexpected_token(const char *input, char *err_message)
{
	int		check;

	if (has_quotes_open(input, err_message)
		|| has_char_at_beginning(input, '|', err_message)
		|| has_char_at_beginning(input, ';', err_message)
		|| has_char_at_end(input, '|', err_message)
		|| has_char_at_end(input, '<', err_message)
		|| has_char_at_end(input, '>', err_message)
		|| has_char_at_end(input, '&', err_message)
		|| has_forbidden_sequence(input, ";;", err_message)
		|| has_forbidden_sequence(input, "|;", err_message)
		|| has_forbidden_sequence(input, "&;", err_message)
		|| has_forbidden_sequence(input, ";|", err_message)
		|| has_forbidden_sequence(input, ";&", err_message)
		|| has_forbidden_sequence(input, ">>>", err_message)
		|| has_spaces_between_char(input, '|', err_message)
		|| has_spaces_between_char(input, '>', err_message))
		check = 0;
	else
		check = 1;
	return (check);
}

/*
** Checks if the user is trying to use a feature not implemented
** @param:	- [const char *] the unchanged line entered in stdin
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
*/

int	is_input_valid_not_supported(const char *input, char *err_message)
{
	int		check;

	if (has_non_supported(input, "<<", err_message)
		|| has_non_supported(input, "*", err_message)
		|| has_non_supported(input, "\\", err_message)
		|| has_non_supported_one(input, "&", err_message))
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
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
** Line-by-line comments:
** @10-11	If we find a double quotes and single quotes are not open,
**			we set has_dquotes_open to its opposite, meaning:
**			- true if it was initially false (we are opening double quotes)
**			- false if it was initially true (we are closing double quotes)
**			We don't care about double quotes if single quotes are open because
**			it will all be part of the token enclosed by the single quotes
** @12-13	Exact same logic as for the double quotes
*/

int	has_quotes_open(const char *input, char *err_message)
{
	int	check;
	int	has_dquotes_open;
	int	has_squotes_open;

	check = 1;
	has_dquotes_open = 0;
	has_squotes_open = 0;
	while (*input)
	{
		if (*input == '"' && has_squotes_open == 0)
			has_dquotes_open = !has_dquotes_open;
		else if (*input == '\'' && has_dquotes_open == 0)
			has_squotes_open = !has_squotes_open;
		input++;
	}
	if (has_dquotes_open || has_squotes_open)
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
**			- [char] the tested character
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
** Line-by-line comments:
** @4-6		We need to trim white space from the input while
**			not changing the initial input
*/

int	has_char_at_beginning(const char *input, char c, char *err_message)
{
	int		check;
	char	*cpy;

	cpy = ft_strtrim(input, WHITE_SPACE);
	if (!cpy)
		quit_program(EXIT_FAILURE);
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
