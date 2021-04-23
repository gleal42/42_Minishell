/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/23 20:15:02 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_list	*cmd_history;
	t_list	*new_node;

	while (1)
	{
		write_prompt();
		new_node = ft_lstnew((void *)get_cmd_table());
		if (!new_node)
			exit(EXIT_FAILURE);
		ft_lstadd_front(&cmd_history, new_node);
		if (((t_cmd_table *)cmd_history->data)->cmds)
			execute_cmd((t_cmd_table *)cmd_history->data, envp);
	}
	return (0);
}
