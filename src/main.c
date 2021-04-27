/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/27 19:13:35 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	t_msh	msh;
	t_dlist	*ast;

	init_minishell(&msh);
	init_termcaps(&msh, &msh.termcaps);
	while (1)
	{
		write_prompt();
		// set_termcaps(msh);
		ast = ft_dlstnew((void *)get_ast());
		if (!ast)
			exit(EXIT_FAILURE);
		ft_dlstadd_front(&msh.cmd_history, ast);
		// print_ast((t_ast *)cmd_history->data);
		if (((t_ast *)msh.cmd_history->data)->cmd_tables)
			execute_cmd((t_ast *)msh.cmd_history->data);
	}
	return (0);
}
