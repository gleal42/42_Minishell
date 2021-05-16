/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/16 13:28:40 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_term.h"

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

/*
** Different types of error messages to best mimic bash. Messages need to be
** sent to STDERR
*/

void	write_msh_error(char *err_message)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	write_exec_error(char *exec_name, char *err_message)
{
	ft_putstr_fd(exec_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	write_msh_exec_error(char *exec_name, char *err_message)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(exec_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	write_msh_exec_arg_error(char *exec_name, char *arg, char *err_message)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(exec_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
