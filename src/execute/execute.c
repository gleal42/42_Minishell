/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:42:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/23 17:36:26 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_cmd(t_cmd_table *cmd_table)
{
	char **tokens;
	int		i;

	i = 0;
	tokens = ((t_cmd *)cmd_table->cmds->data)->tokens;
	if (ft_strcmp(tokens[0], "exit") == 0)
		ft_exit(0);
	else if ()
	return (0);
}

void	ft_exit(int status)
{
	exit(status);
}
/*
 *
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
 * */
