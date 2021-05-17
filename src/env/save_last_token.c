/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_last_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:48:00 by gleal             #+#    #+#             */
/*   Updated: 2021/05/17 09:47:58 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Adds last token to environment variable underscore
** @param:	- [t_cmd_table *] latest command table
** Line-by-line comments:
** @11-12	Last command and token from command table
** @15-20	Edge case: there are no tokens like "> a > b"
*/

void	save_last_token(t_cmd_table *cmd_table)
{
	t_cmd	*last_simple_cmd;
	char	*last_token;
	char	*exec_path;

	last_simple_cmd = ft_lst_get_data_last_node(cmd_table->cmds);
	last_token = ft_lst_get_data_last_node(last_simple_cmd->tokens);
	if (last_token && has_only_one_cmd())
		exec_path = convert_to_path(last_token);
	else
	{
		exec_path = ft_strdup("");
		if (!exec_path)
			quit_program(EXIT_FAILURE);
	}
	update_environment_var("_", exec_path, g_msh.dup_envp);
	free(exec_path);
}

/*
** In case we call an executable inside the path directory, we will get the
** corresponding absolute path
** @param:	- [char *] last token	
** @return:	[char *] string to be stored inside underscore var
*/

char	*convert_to_path(char *token)
{
	char	*token_path;

	if (has_relative_path(token))
	{
		token_path = ft_strdup(token);
		if (!token_path)
			quit_program(EXIT_FAILURE);
	}
	else
		token_path = get_absolute_path(token);
	return (token_path);
}
