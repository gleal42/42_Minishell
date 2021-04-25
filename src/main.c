/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dds <dda-silv@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 13:59:21 by dds              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	t_dlist	*cmd_history;
	t_dlist	*ast;

	while (1)
	{
		write_prompt();
		ast = ft_dlstnew((void *)get_ast());
		if (!ast)
			exit(EXIT_FAILURE);
		ft_dlstadd_front(&cmd_history, ast);
		// print_ast((t_ast *)cmd_history->data);
		if (((t_ast *)cmd_history->data)->cmd_tables)
			execute_cmd((t_ast *)cmd_history->data);
	}
	return (0);
}
