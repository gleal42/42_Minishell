/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 12:21:18 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	t_dlist	*ast;

	(void)argc;
	(void)argv;
	init_minishell(&g_msh, envp);
	while (1)
	{
		write_prompt();
		ast = ft_dlstnew((void *)get_ast());
		if (!ast)
			ft_exit(EXIT_FAILURE);
		ft_dlstadd_front(&g_msh.cmd_history, ast);
		print_ast((t_ast *)g_msh.cmd_history->data);
		if (((t_ast *)g_msh.cmd_history->data)->cmd_tables)
			execute_ast((t_ast *)g_msh.cmd_history->data, &g_msh.dup_envp);
	}
	return (0);
}
