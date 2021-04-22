/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/22 18:33:37 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	write_prompt(void)
{
	int	ret;

	ret = write(STDOUT_FILENO, "$ ", 2);
	(void)ret;
}

void	write_gen_err_message(char *err_message)
{
	ft_putstr("minishell: ");
	ft_putstr(err_message);
	ft_putstr("\n");
}
