/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:30:18 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/24 17:51:49 by dda-silv         ###   ########.fr       */
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
** @4-9		Go through each token and replace it in case there is a dollar sign
** @10-11	Deletes nodes that have an empty token after executiong of
**			replace_env_single_token() (e.g. echo $WRONG_ENV)
** @12-17	Go through each redirection and replace it in case there is a
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
	if (ft_lstsize(*tokens) > 1 && (char)*((char *)(*tokens)->data) != '\0')
		ft_lstclear_if(tokens, is_token_empty, free);
	while (redirs)
	{
		redir = redirs->data;
		replace_env_single_token(&redir->direction);
		redirs = redirs->next;
	}
}

/*
** Replaces token in case of environment variables and special characters. The
** token is split. For instance:
** $ echo "$TERM"'$PATH'hello1"hel'lo2"'hel"lo3'
** xterm-256color$PATHhello1hel'lo2hel"lo3
** So we need to handle each subsegment of the token differently even if there
** isn't a space separating it
** @param:	- [char **] token
** Line-by-line comments:
** @5		Split token in a linked list for ease of manipulation
** @6		We need to keep the head of the linked list to free it when we are
**			done
** @10-11	Tilde expansion only occurs if tilde is first character and is
**			either the only character or followed by a forward slash
** @12		These expansions don't occur if tokens are inbetween single	quotes
** $14-16	Case: the token piece is only $PATH or $TERM
** @19		Replacing $? special parameter with exit status of last cmd
** @21		Deleting unnecessary quotes. See previous example
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
		if (!ft_strcmp(token_piece, "~") || !ft_strncmp(token_piece, "~/", 2))
			replace_tilde_with_home((char **)&tmp->data);
		else if (*token_piece != '\'')
		{
			if (*token_piece == '$' && ft_strcmp(token_piece, "$_") != 0
				&& ft_strcmp(token_piece, "$?") != 0 && *(token_piece + 1) != 0)
				replace_one_var((char **)&tmp->data);
			else
				replace_vars_with_values((char **)&tmp->data);
			replace_status_env((char **)&tmp->data, g_msh.exit_status);
		}
		delete_quotes((char *)tmp->data);
		tmp = tmp->next;
	}
	free(*token);
	*token = join_split_token(split_token);
}

/*
** Finds dollar signs in tokens and replaces the following with the correct
** value
** @param:	- [char *] Tokens (which can be strings with spaces when using
**					   double quotes) 
** Line-by-line comments:
** @14		In case of executables, we don't display the whole path
			(e.g. /bin/ls becomes ls)
** @16		Replaces the token string with another with the respective value
** @17		Replace_midstring() can be emptying the str so that there is only
**			a NULL character as the only character. If we don't check before
**			incrementing, we risk doing a segfault
** @21		We increment for the lenght of the inserted string and decrease one
**			index to account for the '$'
*/

void	replace_vars_with_values(char **str)
{
	int		i;
	char	*var;
	char	*value;
	char	*final;

	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '$' && !ft_strchr("? ", str[0][i + 1])
			&& str[0][i + 1] != '\0')
		{
			var = get_var_name(&str[0][i]);
			if (ft_strcmp(var, "$_") == 0)
				value = get_last_exec_name(var + 1);
			else
				value = ft_getenv(var + 1);
			final = replace_midstring(*str, var, value, i);
			free(*str);
			*str = final;
			free(var);
			i += ft_strlen(value) - 1;
			if (value)
				free(value);
		}
	}
}

/*
** Tilde character gets replaced by home directory if:
** - it is the first character of the token
** - only character in token or followed by forward slash
** - token not between single quotes (they prevent expansions)
** @param:	- [char **] token string
*/

void	replace_tilde_with_home(char **token)
{
	char	*home_path;

	home_path = ft_getenv("HOME");
	if (!token[0][1])
	{
		free(*token);
		*token = home_path;
	}
	else
		tilde_join(token, &home_path);
}

/*
** In case the file refers to an executable from the path files it will be
** replaced by their file names
** @param:	- [char *] "$_"
** @return:	[char *] value to replace $_
** Line-by-line comments:
** @6		Checks if underscore value is an absolute path to a file executable
** @7		Replace full path of executable with its name
*/

char	*get_last_exec_name(char *underscore)
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
