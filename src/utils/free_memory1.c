/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:45:44 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/02 10:36:15 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_memory.h"

/*
** Frees the memory of base struct
** @param:	- [t_msh] base struct of the program
*/

void	free_msh(t_msh *msh)
{
	ft_dlstclear(&msh->input_history, free);
	ft_lstclear(&msh->dup_envp, free);
}
