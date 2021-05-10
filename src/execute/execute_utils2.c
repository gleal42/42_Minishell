/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 22:22:51 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/10 17:59:16 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_utils2.h"

void	close_all_pipes(int **pipes, int nb_cmds)
{
	int	nb_pipes;

	nb_pipes = nb_cmds - 1;
	while (nb_pipes--)
	{
		close(pipes[nb_pipes][0]);
		close(pipes[nb_pipes][1]);
	}
}
