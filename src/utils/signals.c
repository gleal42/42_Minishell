/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:10:23 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/09 16:29:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	catch_signals(int signum)
{
	(void)signum;
	//ft_putstr("\n");
}

void	catch_seg_fault(int signum)
{
	ft_putnbr_fd(signum, STDOUT_FILENO);
	ft_putstr("Segmentation fault\n");
}

void	catch_quitsignal(int signum)
{
	(void)signum;
	ft_putstr("okay\n");
	//signal(SIGQUIT, SIG_DFL);
}