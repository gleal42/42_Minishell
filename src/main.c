/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/23 15:47:56 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	t_list	*cmd_history;
	t_list	*new_node;

	while (1)
	{
		write_prompt();
		new_node = ft_lstnew((void *)get_cmd_table());
		if (!new_node)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&cmd_history, new_node);
		if (!((t_cmd_table *)cmd_history->data)->cmds)
			execute_cmd((t_cmd_table *)cmd_history->data);
	}
	return (0);
}
