/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/30 00:29:01 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	t_ast	*ast;
	t_dlist	*input;

	(void)argc;
	(void)argv;
	init_minishell(&g_msh, envp);
	while (1)
	{
		turn_off_canonical_mode(&g_msh.termcaps);
		write_prompt();
		input = ft_dlstnew((void *)get_input(g_msh.input_history,
											&g_msh.termcaps));
		if (!input)
			ft_exit(EXIT_FAILURE);
		ft_dlstadd_front(&g_msh.input_history, input);
		if (!is_input_valid((const char *)input->data))
			continue ;
		ast = get_ast((const char *)input->data);
		turn_on_canonical_mode(&g_msh.termcaps);
		// print_ast(ast);
		// execute_ast(ast, &g_msh.dup_envp);
		// free_ast(ast);
	}
	return (0);
}
