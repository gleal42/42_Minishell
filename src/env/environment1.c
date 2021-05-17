/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:52:40 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/15 19:28:06 gleal            ###   ########.fr       */
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
	t_redir	*redir;

	token = *tokens;
	while (token)
	{
		replace_env_single_token((char **)&token->data);
		token = token->next;
	}
	ft_lstclear_if(tokens, is_token_empty, free);
	while (redirs)
	{
		redir = redirs->data;
		replace_env_single_token(&redir->direction);
		redirs = redirs->next;
	}
}

/*
** Replaces token in case of environment variables and special characters
** @param:	- [t_token] struct with token strings and delimiter
** Line-by-line comments:
** @6-8		tilde expansion only occurs if tilde is first character and
** 			is either the only character or followed by a forward slash
** @9		these expansions don't occur if tokens are inbetween single
** 			quotes
** @12		replacing $? special parameter with exit status of last cmd
*/

void	replace_env_single_token(char **token)
{
	t_list	*split_token;
	t_list	*tmp;
	char	*token_piece;

	split_token = get_split_token(*token);
	tmp = split_token;
	while (tmp)
	{
		token_piece = tmp->data;
		if (!ft_strcmp(token_piece, "~") || !ft_strcmp(token_piece, "~/"))
			replace_tilde_with_home((char **)&tmp->data);
		else if (*token_piece != '\'')
		{
			replace_vars_with_values((char **)&tmp->data);
			replace_status_env((char **)&tmp->data, g_msh.exit_status);
		}
		delete_quotes((char *)tmp->data);
		tmp = tmp->next;
	}
	free(*token);
	*token = join_split_token(split_token);
	ft_lstclear(&split_token, free);
}

/*
** Finds dollar signs in tokens and replaces the following with the correct
** value
** @param:	- [char *] Tokens (which can be strings with spaces when using
**					   double quotes) 
** Line-by-line comments:
** @13		in case of executables, we don't display the whole path
			(e.g. /bin/ls becomes ls)
** @15		replaces the token string with another with the respective value
** @16		replace_midstring() can be emptying the str so that there is only
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
		if (str[0][i] == '$' && str[0][i + 1] != '?')
		{
			var = get_var_name(&str[0][i]);
			if (ft_strcmp(var, "$_") == 0)
				value = getlastexecname(var + 1);
			else
				value = ft_getenv(var + 1);
			final = replace_midstring(*str, var, value, i);
			free(*str);
			*str = final;
			free(var);
			i += ft_strlen(value);
			if (value)
				free(value);
		}
		else if (str[0][i])
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
** In case the file refers to an executable from the path files it will be
** replaced by their file names
** @param:	- [char *] "$_"
** @return:	[char *] value to replace $_
** Line-by-line comments:
** @6	checks if underscore value is an absolute path to a file executable
** @7	replace full path of executable with its name
*/

char	*getlastexecname(char *underscore)
{
	char	*value;
	char	*temp;

	value = ft_getenv(underscore);
	if (is_path_executable(value))
	{
		temp = ft_strdup(ft_strrchr(value, '/') + 1);
		if (temp == 0)
			quit_program(EXIT_FAILURE);
		free(value);
		value = temp;
		return (value);
	}
	else
		return (value);
}
