/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/21 12:11:49 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**read_prompt(void)
{
	char	**args;

	args = ft_calloc(3, sizeof(char **));
	if (!args)
		exit(EXIT_FAILURE);
	args[0] = ft_strdup("./bin/ft_cat");
	args[1] = ft_strdup("./hello.txt");
	return (args);
}
