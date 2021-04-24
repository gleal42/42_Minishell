/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:42:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 17:44:22 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int		execute_ast(t_ast *ast, t_list **env)
{
	t_list	*cmd_tables;

	cmd_tables = ast->cmd_tables;
	while (cmd_tables)
	{
		execute_cmd_table((t_cmd_table *)cmd_tables->data, env);
		cmd_tables = cmd_tables->next;
	}
	return (0);
}

int		execute_cmd_table(t_cmd_table *cmd_table, t_list **env)
{
	t_list	*cmds;

	cmds = cmd_table->cmds;

	while (cmds)
	{
		//redirection
		execute_cmd((t_cmd *)cmds->data, env);
		cmds = cmds->next;
	}
	return (0);
}

int		execute_cmd(t_cmd *cmd, t_list **env)
{
	(void)env;
	char **tokens;

	tokens = cmd->tokens;
	if (ft_strcmp(tokens[0], "exit") == 0)
		ft_exit(0);
	return (0);
}
void	ft_exit(int status)
{
	exit(status);
}
/*
 *
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
 * */
