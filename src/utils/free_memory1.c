/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:45:44 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/01 17:02:05 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_memory.h"

/*
** Frees the memory of base struct
** @param:	- [t_msh] base struct of the program
** Line-by-line comments:
** @4-5		With the UNIX version of the termcaps lib, we need to set the memory
**			ourselves so we also need to free it
*/

void	free_msh(t_msh *msh)
{
	ft_dlstclear(&msh->input_history, free);
	free_ast(msh->ast);
	if (IS_UNIX)
		free(g_msh.termcaps.buffer);
	ft_lstclear(&msh->dup_envp, free);
}
