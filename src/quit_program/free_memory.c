/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:23:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 11:25:40 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_memory.h"

/*
** Frees the memory of base struct
** @param:	- [t_msh *] base struct of the program
** Line-by-line comments:
** @1-2		Both input_history and dup_envp only have strings as nodes so
** 			passing free is enough
** @3-4		But ast is a struct so we had to get a bit fancy
*/

void	free_msh(t_msh *msh)
{
	ft_dlstclear(&msh->input_history, free);
	ft_lstclear(&msh->dup_envp, free);
	if (msh->ast != 0)
		free_ast(msh->ast);
}

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
