/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/29 10:14:47 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	write_prompt(void)
{
	ft_putstr(GREEN);
	ft_putstr("msh$ ");
	ft_putstr(RESET);
}

void	write_gen_err_message(char *err_message)
{
	ft_putstr("minishell: ");
	ft_putstr(err_message);
	ft_putstr("\n");
}
