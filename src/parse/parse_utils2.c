/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 08:34:51 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/05 10:26:57 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

void	delete_backslashes(t_token *token)
{
	char	*str;
	int		i;

	if (token->delimiter != ' ')
		return ;
	i = 0;
	str = token->str;
	while (str[i])
	{
		if (str[i] == '\\' && (is_delimiter(str[i + 1])
			|| str[i + 1] == '\'' || str[i + 1] == '"'))
			ft_strcpy(&str[i], (const char *)&str[i + 1]);
		i++;
	}
}

void	delete_quotes(char *str)
{
	int	i;
	int	has_dquotes_open;
	int	has_squotes_open;

	i = 0;
	has_dquotes_open = 0;
	has_squotes_open = 0;
	while (str[i])
	{
		if (str[i] == '"' && has_squotes_open == 0)
		{
			has_dquotes_open = !has_dquotes_open;
			ft_strcpy(&str[i], (const char *)&str[i + 1]);
		}
		if (str[i] == '\'' && has_dquotes_open == 0)
		{
			has_squotes_open = !has_squotes_open;
			ft_strcpy(&str[i], (const char *)&str[i + 1]);
		}
		i++;
	}
}
