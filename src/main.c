/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 14:34:31 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_list	*cmd_history;
	t_list	*ast;

	while (1)
	{
		write_prompt();
		ast = ft_lstnew((void *)get_ast());
		if (!ast)
			exit(EXIT_FAILURE);
		ft_lstadd_front(&cmd_history, ast);
		if (((t_ast *)cmd_history->data)->nb_cmd_tables > 0)
			execute_cmd((t_ast *)cmd_history->data);
	}
	return (0);
}
