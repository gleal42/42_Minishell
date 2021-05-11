/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 11:07:39 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/11 11:30:39 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_prog.h"

/*
** Exits the program by doing some cleaning before
** @param:	- [int] exit_code, either EXIT_SUCCESS or EXIT_FAILURE
** Line-by-line comments:
** @4-5		When "ks" termcap is used, we need to turn it off before exiting
** @6		In this program we have tweaked the terminal default settings so
**			we need to make sure they are as they were when the program started
*/

void	exit_prog(int exit_code)
{
	t_termcaps *termcaps;

	termcaps = &g_msh.termcaps;
	if (termcaps->keys_off)
		tputs(termcaps->keys_off, 1, ft_putint);
	turn_on_canonical_mode(termcaps);
	free_msh(&g_msh);
	exit(exit_code);
}
