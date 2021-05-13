/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:49:51 by gleal             #+#    #+#             */
/*   Updated: 2021/05/10 16:55:22by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"

/*
** Recreating the exit function based on different arguments. Mimics bash
** @param:	- [t_list *] a list of all the arguments used with the exit cmd
** Line-by-line comments:
** @4-5		Case: no arguments so the exit status sent is the one of the last
**			executed simple command (e.g. cd asjoafsj; exit; echo $? STDOUT: 1)
** @7-8		Case: first arg is a number but there are more than one arg. Doesn't
**			exit. Sends error message and returns EXIT_FAILURE
** @9-15	Case: non-numeric argument. Exits with error message
** @16-17	Case: arg is a number and only one arg. Exits with arg as exit code
*/

int	ft_exit(t_list *exit_arguments)
{
	char	*first_argument;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (exit_arguments == 0)
		quit_program(g_msh.exit_status);
	first_argument = ((t_token *)exit_arguments->data)->str;
	if (ft_strisnumber(first_argument) && exit_arguments->next != 0)
		write_gen_err_message("exit: too many arguments");
	else if (!ft_strisnumber(first_argument))
	{
		ft_putstr_fd("msh: exit: ", STDERR_FILENO);
		ft_putstr_fd(first_argument, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		quit_program(EXIT_GENERAL_ERROR);
	}
	else if (ft_strisnumber(first_argument) && exit_arguments->next == 0)
		quit_program(ft_atoi(first_argument));
	return (EXIT_FAILURE);
}
