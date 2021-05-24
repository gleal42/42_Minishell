/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:41:56 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/24 17:10:22 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"

/*
** Recreating the exit function based on different arguments. Mimics bash
** @param:	- [t_list *] a list of all the arguments used with the exit cmd
** Line-by-line comments:
** @3-4		exit doesn't have to exit if there are more than one simple command
**			in cmd_table but it still has to do thorough error handling
** @5-6		Case: no arguments so the exit status sent is the one of the last
**			executed simple command (e.g. cd asjoafsj; exit; echo $? STDOUT: 1)
** @10-11	Case: first arg is a number but there are more than one arg. Doesn't
**			exit. Sends error message and returns EXIT_FAILURE
** @12-19	Case: non-numeric argument. Exits with error message
** @20-21	Case: arg is a number and only one arg. Exits with arg as exit code
*/

int	ft_exit(t_list *args)
{
	char	*arg;

	if (has_only_one_cmd())
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args == 0 && has_only_one_cmd())
		quit_program(g_msh.exit_status);
	else if (args == 0 && !has_only_one_cmd())
		return (EXIT_SUCCESS);
	arg = args->data;
	if (ft_strisnumber(arg) && args->next != 0)
		write_msh_exec_error("exit", "too many arguments");
	else if (!ft_strisnumber(arg))
	{
		write_msh_exec_arg_error("exit", arg, "numeric argument required");
		if (has_only_one_cmd())
			quit_program(EXIT_GENERAL_ERROR);
		else
			return (EXIT_GENERAL_ERROR);
	}
	else if (ft_strisnumber(arg) && args->next == 0 && has_only_one_cmd())
		quit_program(ft_atoi(arg));
	else if (ft_strisnumber(arg) && args->next == 0 && !has_only_one_cmd())
		return (ft_atoi(arg));
	return (EXIT_FAILURE);
}
