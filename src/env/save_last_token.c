/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_last_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:48:00 by gleal             #+#    #+#             */
/*   Updated: 2021/05/14 04:12:50 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Adds last token to environment variable underscore
** @param:	- [t_cmd_table *] latest command table
** Line-by-line comments:
** @6-10	last command and token from command table
*/

void	save_last_token(t_cmd_table *cmd_table)
{
	t_list	*cmds;
	t_list	*tokens;
	char	*exec_path;

	cmds = cmd_table->cmds;
	while (cmds->next != 0)
		cmds = cmds->next;
	tokens = ((t_cmd *)(cmds->data))->tokens;
	while (tokens->next != 0)
		tokens = tokens->next;
	exec_path = convert_to_path(((t_token *)(tokens->data))->str);
	update_environment_var("_", exec_path, g_msh.dup_envp);
	free(exec_path);
}

/*
** In case we call an executable inside the path directory,
** we will get the corresponding absolute path
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