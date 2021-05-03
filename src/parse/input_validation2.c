/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:37:13 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/03 10:43:16 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_validation.h"

/*
** Checks if there is a specific character at end of input
** @param:	- [const char *] the unchanged line entered in stdin
** @return:	[int] true or false
** Line-by-line comments:
** @5-8		We need to trim white space from the input while
**			not changing the initial input
*/

int	has_char_at_end(const char *input, char c, char *err_message)
{
	int		check;
	char	*cpy;
	int		len;

	cpy = ft_strtrim(input, " \t\n\v\f\r");
	if (!cpy)
		ft_exit(EXIT_FAILURE);
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

int	has_non_supported(const char *input, char *test, char *err_message)
{
	int	check;

	if (ft_strstr_quotes((char *)input, test) != 0)
	{
		check = 1;
		ft_strcpy(err_message, test);
		ft_strcat(err_message, " not supported");
	}
	else
		check = 0;
	return (check);
}

int	has_str(const char *input, char *test, char *err_message)
{
	int		check;
	char	*trimmed;

	trimmed = ft_strtrim_all(input, " \t\n\v\f\r");
	if (!trimmed)
		ft_exit(EXIT_FAILURE);
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

int	has_spaces_between_char(const char *input, char c, char *err_message)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			skip_quotes((char *)input, &i);
		if (input[i] == c && input[i + 1] == ' ')
		{
			i++;
			skip_spaces((char *)input, &i);
			if (input[i] == c)
			{
				check = 1;
				ft_strcpy(err_message, "syntax error near unexpected token `");
				ft_strncat(err_message, &c, 1);
				ft_strcat(err_message, "'");
				break ;
			}
		}
		i++;
	}
	return (check);
}
