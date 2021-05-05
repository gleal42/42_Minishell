/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 08:34:51 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/05 15:52:59 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

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
** @return:	[type] return_value
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
