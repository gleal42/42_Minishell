/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 10:40:58 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 10:43:54 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_ast.h"

/*
** Functions below will be deleted when project is finished
*/

void	print_ast(t_ast *ast)
{
	t_list	*cmd_table;

	printf("print_ast:\n");
	printf("raw_input: \"%s\"\n", ast->raw_input);
	printf("nb_cmd_tables: %d\n", ft_lstsize(ast->cmd_tables));
	cmd_table = ast->cmd_tables;
	while (cmd_table)
	{
		print_cmd_table(cmd_table->data);
		cmd_table = cmd_table->next;
		printf("\n");
	}
}

void	print_cmd_table(t_cmd_table *cmd_table)
{
	t_list	*cmd;

	printf("\n");
	printf("print_cmd_table:\n");
	printf("nb_cmds: %d\n", ft_lstsize(cmd_table->cmds));
	printf("delimiter: \"%s\"\n", cmd_table->delimiter);
	cmd = cmd_table->cmds;
	while (cmd)
	{
		print_cmd(cmd->data);
		cmd = cmd->next;
		printf("\n");
	}
}

void	print_cmd(t_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	printf("\n");
	printf("print_cmd\n");
	i = 0;
	while (cmd->tokens[i])
	{
		printf("Tokens[%d]: \"%s\"\n", i, cmd->tokens[i]);
		i++;
	}
	tmp = cmd->redirs;
	printf("nb_redirs: %d\n", ft_lstsize(cmd->redirs));
	while (tmp)
	{
		print_redir(tmp->data);
		tmp = tmp->next;
		printf("\n");
	}
}

void	print_redir(t_redir *redir)
{
	printf("direction: \"%s\"\n", redir->direction);
	printf("type: \"%s\"\n", redir->type);
	printf("is_executable: %d\n", redir->is_executable);
}
