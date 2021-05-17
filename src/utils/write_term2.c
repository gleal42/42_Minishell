/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_term2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 00:51:36 by gleal             #+#    #+#             */
/*   Updated: 2021/05/17 03:06:18 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_term.h"

void	write_msh_exec_arg_error_nocolon(char *exec_name,
			char *arg, char *err_message)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(exec_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
