/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:23:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/16 18:46:27 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_ast.h"

/*
** Frees the Abstract Syntax Tree struct
** Besides free_ast, all functions in this file are made to be passed to the
** ft_lstclear function as a function pointer to free each node. But we also
** need to free the struct itself when we are done with the linked list
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
	free(((t_cmd_table *)cmd_table)->delimiter);
	free(cmd_table);
}

void	free_cmd(void *cmd)
{
	ft_lstclear(&((t_cmd *)cmd)->tokens, free);
	ft_lstclear(&((t_cmd *)cmd)->redirs, free_redir);
	free(cmd);
}

void	free_redir(void *redir)
{
	free(((t_redir *)redir)->direction);
	free(redir);
}
