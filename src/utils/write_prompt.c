/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 11:29:40 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_prompt.h"

/*
** Displays the prompt to the user
** Line-by-line comments:
** @1-4		Color of the prompt will the depend on the last exit_status
** @6		Set back the color to white
*/

void	write_prompt(void)
{
	if (g_msh.exit_status == EXIT_SUCCESS)
		ft_putstr(GREEN);
	else
		ft_putstr(RED);
	ft_putstr("msh → ");
	ft_putstr(RESET);
}
