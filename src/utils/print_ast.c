/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 10:40:58 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 12:21:52 by dda-silv         ###   ########.fr       */
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
	t_list	*token;
	t_list	*redir;

	printf("\n");
	printf("print_cmd\n");
	i = 0;
	token = cmd->tokens;
	printf("nb_tokens: %d\n", ft_lstsize(cmd->tokens));
	while (token)
	{
		print_token(token->data, i);
		token = token->next;
		i++;
	}
	redir = cmd->redirs;
	printf("nb_redirs: %d\n", ft_lstsize(cmd->redirs));
	while (redir)
	{
		print_redir(redir->data);
		redir = redir->next;
		printf("\n");
	}
}

void	print_token(t_token *token, int i)
{
	printf("token n°%d: str: \"%s\"", i, token->str);
	printf(" & delimiter: \"%c\"\n", token->delimiter);
}

void	print_redir(t_redir *redir)
{
	printf("direction: \"%s\"\n", ((t_token *)redir->direction)->str);
	printf("type: \"%s\"\n", redir->type);
}
