/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:37:13 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/02 20:34:53 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_validation.h"

int	has_str(const char *input, char *test, char *error_message)
{
	int		check;
	char	*trimmed;

	trimmed = ft_strtrim_all(input, " \t\n\v\f\r");
	if (!trimmed)
		ft_exit(EXIT_FAILURE);
	if (ft_strstr_quotes(trimmed, test) != 0)
	{
		check = 1;
		ft_strcpy(error_message, "syntax error near unexpected token `");
		ft_strncat(error_message, test, 1);
		ft_strcat(error_message, "'");

	}
	else
		check = 0;
	free(trimmed);
	return (check);
}

int	has_spaces_between_char(const char *input, char c, char *error_message)
{
	int		check;
	int		has_double_quotes_open;
	int		has_single_quotes_open;

	check = 0;
	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (*input)
	{
		if (*input == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (*input == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		else if (has_double_quotes_open || has_single_quotes_open)
			;
		else if (*input == c && *(input + 1) == ' ')
		{
			input++;
			while (ft_isspace(*input))
				input++;
			if (*input == c)
			{
				check = 1;
				ft_strcpy(error_message, "syntax error near unexpected token `");
				ft_strncat(error_message, &c, 1);
				ft_strcat(error_message, "'");
				break ;
			}
		}
		input++;
	}
	return (check);
}


char	*ft_strstr_quotes(char *str, char *to_find)
{
	int		has_double_quotes_open;
	int		has_single_quotes_open;

	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	if (!(*to_find))
		return (str);
	while (*str)
	{
		if (*str == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (*str == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		else if (has_double_quotes_open || has_single_quotes_open)
			;
		else if (!ft_strncmp(str, to_find, ft_strlen(to_find)))
			return (str);
		str++;
	}
	return (0);
}
