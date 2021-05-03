/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:23:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/01 17:26:22 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_memory.h"

/*
** Frees the ast struct.
** Besides free_ast, all functions in this file are made to be passed to the
** ft_lstclear function
** @param:	- [t_ast *] struct with the abstract syntax tree
*/

void	free_ast(t_ast *ast)
{
	ft_lstclear(&ast->cmd_tables, free_cmd_table);
	free(ast);
}

void	free_cmd_table(void *cmd_table)
{
	ft_lstclear(&((t_cmd_table *)cmd_table)->cmds, free_cmd);
}

void	free_cmd(void *cmd)
{
	ft_lstclear(&((t_cmd *)cmd)->tokens, free_token);
	ft_lstclear(&((t_cmd *)cmd)->redirs, free_redir);
}

void	free_redir(void *redir)
{
	free_token(((t_redir *)redir)->direction);
}

void	free_token(void *token)
{
	free(((t_token *)token)->str);
}
