/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:42:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 21:33:19 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int		execute_ast(t_ast *ast, t_list **env)
{
	t_list	*cmd_table;

	cmd_table = ast->cmd_tables;
	while (cmd_table)
	{
		execute_cmd_table((t_cmd_table *)cmd_table->data, env);
		cmd_table = cmd_table->next;
	}
	return (0);
}

int		execute_cmd_table(t_cmd_table *cmd_table, t_list **env)
{
	t_list	*cmds;
	int		pipe;

	cmds = cmd_table->cmds;
	while (cmds)
	{
		//redirection
		if (cmds->next == NULL)
			pipe = 0;
		else
			pipe = 1;
		execute_cmd((t_cmd *)cmds->data, env, pipe);
		cmds = cmds->next;
	}
	return (0);
}

int		execute_cmd(t_cmd *cmd, t_list **env, int pipe)
{
	char **tokens;

	(void)env;
	tokens = cmd->tokens;
	env_vars(&tokens, env);
	if (ft_strcmp(tokens[0], "exit") == 0 && pipe == 0)
		ft_exit(0);
	else if (is_builtin(tokens[0]))
		execute_builtin(tokens);
	return (0);
}

void	ft_exit(int status)
{
	exit(status);
}
