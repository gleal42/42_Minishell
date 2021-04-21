/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:47:34 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/21 12:11:29 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char *argv[])
{
	char	**args;
	char	**envp;

	envp = ft_calloc(2, sizeof(char *));
	envp[0] = ft_strdup("PATH=/bin");
	envp[1] = 0;

	write_prompt();
	args = read_prompt();
	if (fork() != 0)
		wait(NULL);
	else
		execve(args[0], args, envp);

	free_arr((void **)args);
	free_arr((void **)envp);
	return (0);
	(void)argc;
	(void)argv;
}
