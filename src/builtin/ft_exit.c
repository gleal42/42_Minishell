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

#include "builtins.h"

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

void	ft_exit(t_list *cmds)
{
	t_list	*first_argument;

	first_argument = ((t_cmd *)(cmds->data))->tokens->next;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (first_argument == 0)
		exit_prog(g_msh.exit_status);
	else if (ft_strisnumber(((t_token *)first_argument->data)->str))
	{
		if (first_argument->next == 0)
			exit_prog(ft_atoi(((t_token *)first_argument->data)->str));
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
		exit_prog(EXIT_GENERAL_ERROR);
	}
}
