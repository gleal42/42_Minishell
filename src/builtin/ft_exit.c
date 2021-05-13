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
** checks if this is a valid exit call:
** @param:	- [type] param_value
**			- [type] param_value
** @return:	[type] return_value
** Line-by-line comments:
** @10-11	exit not valid in case of pipes
**			(multiple commands)
*/

int	is_exit(t_list *cmds)
{
	t_list	*tokens_first_cmd;
	t_list	*second_cmd;

	if (cmds == 0)
		return (0);
	tokens_first_cmd = ((t_cmd *)(cmds->data))->tokens;
	if (ft_strcmp(((t_token *)tokens_first_cmd->data)->str, "exit") == 0)
	{
		second_cmd = cmds->next;
		if (second_cmd != 0)
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

/*
** Recreating the exit function based on different arguments
** @param:	- [t_list *] all commands in current command table
** Line-by-line comments:
** @5-6		no arguments exit status remains the previous one
			(e.g. cd asjoafsj; exit; echo $? STDOUT: 1)
** @7		in case of first argument is a number 2 things can happen:
** @9		- if it is the single argument the exit status is that number
** @10		- in case of multiple arguments an error message is shown and
** 			exits failure
** @18-24	in case of non-numeric argument a general error is 
** 			displayed in stderror
*/

void	ft_exit(t_list *cmds)
{
	t_list	*first_argument;

	first_argument = ((t_cmd *)(cmds->data))->tokens->next;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (first_argument == 0)
		quit_program(g_msh.exit_status);
	else if (ft_strisnumber(((t_token *)first_argument->data)->str))
	{
		if (first_argument->next == 0)
			quit_program(ft_atoi(((t_token *)first_argument->data)->str));
		else
		{
			write_gen_err_message("exit: too many arguments");
			g_msh.exit_status = EXIT_FAILURE;
			return ;
		}
	}
	else
	{
		ft_putstr_fd("msh: exit: ", STDERR_FILENO);
		ft_putstr_fd(((t_token *)first_argument->data)->str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		quit_program(EXIT_GENERAL_ERROR);
	}
}
