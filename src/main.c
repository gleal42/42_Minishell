/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/22 18:41:46 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	// t_dlist	cmd_history;
	t_cmd_table	*cmd_table;

	while (1)
	{
		write_prompt();
		cmd_table = (void *)get_cmd_table();
		printf("\"%s\"\n", cmd_table->raw_input);
		// if (!cmd_history->data->cmds)
		// 	execute_cmd((t_cmd_table *)cmd_history->data);
	}
	return (0);
}
