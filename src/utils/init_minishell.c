/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:58:07 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/17 19:01:51by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_minishell.h"

/*
** Set a few things the program needs to run
** @param:	- [t_msh *] main struct of the program
**			- [char **] environment pointers that we need to duplicate
** Line-by-line comments:
** @1-2		Makes sure that the terminal is linked to the STDIN
** @6		Increases SHLVL environment variable everytime we call 
** 			./minishell inside another one
*/

void	init_minishell(t_msh *msh, char **envp)
{
	if (!isatty(STDIN_FILENO))
		quit_program(EXIT_FAILURE);
	ft_bzero(msh, sizeof(t_msh));
	duplicate_env(&msh->dup_envp, envp);
	unset_oldpwd();
	increment_shlvl();
	init_termcaps(&msh->termcaps);
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, catch_sigquit);
}
