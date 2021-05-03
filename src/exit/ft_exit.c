/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:32:51 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/03 17:34:19 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"

/*
** Exits the program by doing some cleaning before
** @param:	- [int] exit_code, either EXIT_SUCCESS or EXIT_FAILURE
** Line-by-line comments:
** @1-2		When "ks" termcap is used we need to turn it off before exiting
** @3		In this program we have tweaked the terminal default settings so
**			we need to make sure they are as they were when the program started
*/

void	ft_exit(int exit_code)
{
	if (g_msh.termcaps.keys_off)
		tputs(g_msh.termcaps.keys_off, 1, ft_putint);
	turn_on_canonical_mode(&g_msh.termcaps);
	free_msh(&g_msh);
	exit(exit_code);
}
