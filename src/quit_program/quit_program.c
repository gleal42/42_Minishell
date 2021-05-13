/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 11:07:39 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 16:55:35 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quit_program.h"

/*
** Exits the program by doing some cleaning before
** @param:	- [int] exit_code, like EXIT_SUCCESS or EXIT_FAILURE
** Line-by-line comments:
** @4-5		When "ks" termcap is used, we need to turn it off before exiting
** @6		In this program we have tweaked the terminal default settings so
**			we need to make sure they are as they were when the program started
*/

void	quit_program(int exit_code)
{
	t_termcaps	*termcaps;

	termcaps = &g_msh.termcaps;
	if (termcaps->keys_off)
		tputs(termcaps->keys_off, 1, ft_putint);
	turn_on_canonical_mode(termcaps);
	free_msh(&g_msh);
	exit(exit_code);
}

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
