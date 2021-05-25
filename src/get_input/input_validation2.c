/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:37:13 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 10:59:53 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_validation.h"

/*
** Checks if there is a specific character at end of input
** @param:	- [const char *] the unchanged line entered in stdin
**			- [char] the tested character
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
** Line-by-line comments:
** @5-8		We need to trim white space from the input while not changing the
**			initial input
*/

int	has_char_at_end(const char *input, char c, char *err_message)
{
	int		check;
	char	*cpy;
	int		len;

	cpy = ft_strtrim(input, WHITE_SPACE);
	if (!cpy)
		quit_program(EXIT_FAILURE);
	len = ft_strlen(cpy);
	if (cpy[len - 1] == c)
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

/*
** Checks if the input has a syntax error regardless of spaces between
** implemented
** @param:	- [const char *] the unchanged line entered in stdin
**			- [char *] tested string that has non-supported feature like "&&"
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
** Line-by-line comments:
** @4		ft_strstr_all returns a string with all the referenced characters
**			trimmed
** @7		ft_strstr_quotes behaves like strstr but it doesn't looks for
** 			the tested string between quotes (single or double). So if
**			ft_strstr_quotes returns the address of where it found test, it
**			means that the input has a syntax error
*/

int	has_forbidden_sequence(const char *input, char *test, char *err_message)
{
	int		check;
	char	*trimmed;

	trimmed = ft_strtrim_all(input, WHITE_SPACE);
	if (!trimmed)
		quit_program(EXIT_FAILURE);
	if (ft_strstr_quotes(trimmed, test) != 0)
	{
		check = 1;
		ft_strcpy(err_message, "syntax error near unexpected token `");
		ft_strncat(err_message, test, 1);
		ft_strcat(err_message, "'");
	}
	else
		check = 0;
	free(trimmed);
	return (check);
}

/*
** Checks if a character is found twice with only spaces between them.
** Example:
** - "test | test" is valid but "test |   | test" isn't
** - "test > log.txt" and "test >> log.txt" are valid but "test >  > log" isn't
** @param:	- [const char *] the unchanged line entered in stdin
**			- [char] tested char
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
** Line-by-line comments:
** @8-9		If we find a single or double quote, skip_quotes parses through
** 			the input until the quote found is closed
** 10-14	If we find a '|' and a space, we check that the next non-space
**			character is equal to '|'. If it is, then the input is invalid
** @20-21	Both skip_quotes and skip_spaces do some parsing and they could
**			reach the end of the string so we need to check that before
** 			incrementing otherwise we segfault
*/

int	has_spaces_between_char(const char *input, char c, char *err_message)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			skip_quotes(input, &i);
		if (input[i] == c && input[i + 1] == ' ')
		{
			i++;
			skip_spaces((char *)input, &i);
			if (input[i] == c)
			{
				ft_strcpy(err_message, "syntax error near unexpected token `");
				ft_strncat(err_message, &c, 1);
				ft_strcat(err_message, "'");
				return (1);
			}
		}
		if (input[i])
			i++;
	}
	return (0);
}

/*
** Checks if the input is trying to use a specific bash feature that isn't
** implemented
** @param:	- [const char *] the unchanged line entered in stdin
**			- [char *] tested string that has non-supported feature like "&&"
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
** Line-by-line comments:
** @3		ft_strstr_quotes behaves like strstr but it doesn't looks for
** 			the tested string between quotes (single or double). So if
**			ft_strstr_quotes returns the address of where it found test, it
**			means that the input has a non-supported bash feature
*/

int	has_non_supported(const char *input, char *test, char *err_message)
{
	int		check;

	if (ft_strstr_quotes((char *)input, test) != 0)
	{
		check = 1;
		ft_strcpy(err_message, "\"");
		ft_strcat(err_message, test);
		ft_strcat(err_message, "\" not supported");
	}
	else
		check = 0;
	return (check);
}

/*
** Checks if the input is trying to use a specific bash feature that isn't
** implemented. Different from has_non_supported() because it checks if the
** the tested string is present separeted from a same character.
** For instance, "echo && test" is valid but "echo & test" isn't
** @param:	- [const char *] the unchanged line entered in stdin
**			- [char *] tested string that has non-supported feature like "&&"
**			- [char *] empty string with 100 chars of space where to write the
**                     error message
** @return:	[int] true or false
** Line-by-line comments:
** @8		ft_strstr_quotes behaves like strstr but it doesn't looks for
** 			the tested string between quotes (single or double). So if
**			ft_strstr_quotes returns the address of where it found test, it
**			means that the input has a non-supported bash feature
** @14-15	If we found one occurence of the tested string but it's repeated
**			we need to finish parsing the string to see if there are more
**			occurences
*/

int	has_non_supported_one(const char *input, char *test, char *err_message)
{
	int		check;
	char	*tmp;

	check = 0;
	tmp = (char *)input;
	while (tmp)
	{
		tmp = ft_strstr_quotes(tmp, test);
		if (tmp != 0 && *(tmp + 1) != *test)
		{
			check = 1;
			break ;
		}
		else if (tmp != 0 && *(tmp + 1) == *test)
			tmp += 2;
	}
	if (check)
	{
		ft_strcpy(err_message, "\"");
		ft_strcat(err_message, test);
		ft_strcat(err_message, "\" not supported");
	}
	return (check);
}
