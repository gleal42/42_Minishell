/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:55:52 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 14:41:07 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	init_termcaps(t_termcaps *termcaps)
{
	if (IS_UNIX)
	{
		termcaps->buffer = ft_calloc(2048, 1);
		if (!termcaps->buffer)
			ft_exit(EXIT_FAILURE);
	}

}
