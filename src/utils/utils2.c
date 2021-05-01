/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:05:29 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/01 17:00:21 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils2.h"

/*
** Set a few things the program needs to run
** @param:	- [t_msh *] main struct of the program
**			- [char **] environment pointers that we need to duplicate
** Line-by-line comments:
** @1-2		Makes sure that the terminal is linked to the STDIN
*/

void	init_minishell(t_msh *msh, char **envp)
{
	if (!isatty(STDIN_FILENO))
		ft_exit(EXIT_FAILURE);
	ft_bzero(msh, sizeof(msh));
	duplicate_env(&msh->dup_envp, envp);
	init_termcaps(&msh->termcaps);
}

/*
** Exits the program by doing some cleaning before
** @param:	- [int] exit_code, either EXIT_SUCCESS or EXIT_FAILURE
** Line-by-line comments:
** @1-2		When "ks" termcap is used we need to turn it off before exiting
** @3		In this program we have tweaked the terminal default settings so
**			we need to make sure they are as they were when the program started
*/

void	ft_exit(int exit_code)
{
	if (g_msh.termcaps.keys_off)
		tputs(g_msh.termcaps.keys_off, 1, ft_putint);
	turn_on_canonical_mode(&g_msh.termcaps);
	free_msh(&g_msh);
	exit(exit_code);
}

void	duplicate_env(t_list **dup_envp, char **envp)
{
	t_list	*next_env;
	int		i;
	char	*tmp;

	if (!envp || !envp[0])
		ft_exit(EXIT_FAILURE);
	i = 0;
	while (envp[i] != NULL)
	{
		tmp = ft_strdup(envp[i]);
		if (!tmp)
			ft_exit(EXIT_FAILURE);
		next_env = ft_lstnew(tmp);
		if (!next_env)
			ft_exit(EXIT_FAILURE);
		ft_lstadd_back(dup_envp, next_env);
		i++;
	}
}

char	*ft_getenv(char *key)
{
	int		i;
	t_list	*envp;
	char	*curr_envp;
	char	*value;

	envp = g_msh.dup_envp;
	while (envp)
	{
		i = 0;
		curr_envp = (char *)envp->data;
		while (key[i] && curr_envp[i] && (key[i] == curr_envp[i]))
			i++;
		if (!key[i] && curr_envp[i] == '=')
		{
			value = ft_strdup(&(curr_envp[i + 1]));
			if (!value)
				ft_exit(EXIT_FAILURE);
			return (value);
		}
		envp = envp->next;
	}
	return (0);
}
