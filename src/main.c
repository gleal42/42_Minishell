/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 17:44:38 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmd_history;
	t_list	*ast;
	t_list	*env;

	(void)argc;
	(void)argv;
	env = dup_env(envp);
	//ft_lst_print_s(env);
	while (1)
	{
		write_prompt();
		ast = ft_lstnew((void *)get_ast());
		if (!ast)
			exit(EXIT_FAILURE);
		ft_lstadd_front(&cmd_history, ast);
		if (((t_ast *)cmd_history->data)->nb_cmd_tables > 0)
			execute_ast((t_ast *)cmd_history->data, &env);
	}
	return (0);
}
