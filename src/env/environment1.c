/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:52:40 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/15 15:18:24 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Goes through token and redirections list and replaces environment variables
** by the respective values in case there are special characters:
** - '$' followed by an environment variable - value in env var global variable
** - '~' - HOME directory
** - '$?' - last exit status
** (except for single quotes delimiter)
** @param:	- [t_list *] list of token strings that will be analyzed
**			- [t_list *] list of redirections strings that will be analyzed
** Line-by-line comments:
** @6-7		Go through each token and replace it in case there is a dollar sign
** @12-13	Go through each redirection and replace it in case there is a
**			dollar sign ($)
*/

void	replace_envs(t_list **tokens, t_list *redirs)
{
	t_list	*token;

	token = *tokens;
	while (token)
	{
		replace_env_single_token(token->data);
		token = token->next;
	}
	ft_lstclear_if(tokens, is_token_empty, free_token);
	while (redirs)
	{
		replace_env_single_token(((t_redir *)redirs->data)->direction);
		redirs = redirs->next;
	}
}

/*
** Replaces token in case of environment variables and special characters
** @param:	- [t_token] struct with token strings and delimiter
** Line-by-line comments:
** @6-8		Tilde expansion only occurs if tilde is first character and
** 			is either the only character or followed by a forward slash
** @9		these expansions don't occur if tokens are inbetween single
** 			quotes
** @12		Special params only refers to the $? case (other special
**			case expansions are not included)
*/

void	replace_env_single_token(t_token *token)
{
	char	**str;
	char	delimiter;

	str = &token->str;
	delimiter = token->delimiter;
	if (delimiter == ' ' && str[0][0] == '~'
		&& (str[0][1] == '\0' || str[0][1] == '/'))
		replace_tilde_with_home(str);
	if (delimiter != '\'')
	{
		replace_vars_with_values(str);
		replace_special_params(str);
	}
}

/*
** Finds dollar signs in tokens and replaces the following with the correct
** value
** @param:	- [char *] Tokens (which can be strings with spaces when using
**					   double quotes) 
** Line-by-line comments:
** @13		Replaces the token string with another with the respective value
** @20-21	replace_midstring() can be emptying the str so that there is only
**			a NULL character as the only character. If we don't check before
**			incrementing, we risk doing a segfault
*/

void	replace_vars_with_values(char **str)
{
	int		i;
	char	*var;
	char	*value;
	char	*final;

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '$' && (str[0][i + 1] != '?' && str[0][i + 1] != '_'))
		{
			var = get_var_name(&str[0][i]);
			value = ft_getenv(var + 1);
			final = replace_midstring(*str, var, value, i);
			free(*str);
			*str = final;
			free(var);
			if (value)
				free(value);
		}
		if (str[0][i])
			i++;
	}
}

/*
** Tilde character gets replaced by home directory if:
** - it is the first character of the token
** - only character in token or followed by forward slash
** - token not between single quotes (they prevent expansions)
** @param:	- [t_token *] struct with token strings and delimiter information
*/

void	replace_tilde_with_home(char **str)
{
	char	*home_path;

	home_path = ft_getenv("HOME");
	if (!str[0][1])
	{
		free(*str);
		*str = home_path;
	}
	else
		tilde_join(str, &home_path);
}

/*
** Used at the moment simply to replace $? for the exit status of the previous
** function
** @param:	- [char **] pointer to token string in linked list
**			- [int] exit status from last function executed
** Line-by-line comments:
** @5		Function that finds the place where we will replace the substring
** 			(iterator as opposed to string pointer)
*/

void	replace_special_params(char **str)
{
	replace_status_env(str, g_msh.exit_status);
	replace_underscore_env(str);
}
