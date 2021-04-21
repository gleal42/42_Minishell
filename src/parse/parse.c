/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/21 19:59:16 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd_table	*get_cmd(void)
{
	char	*raw_cmd;
	adj_get_next_line(0, &raw_cmd);
	if (!raw_cmd)
		exit(EXIT_FAILURE);

	return (0);
}
