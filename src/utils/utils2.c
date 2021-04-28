/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:05:29 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 10:59:20 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils2.h"

void	init_minishell(t_msh *msh, char **envp)
{
	ft_bzero(msh, sizeof(msh));
	duplicate_env(msh, envp);
	if (!isatty(STDIN_FILENO))
		ft_exit(EXIT_FAILURE);
}

void	ft_exit(int exit_code)
{
	free_msh(&g_msh);
	exit(exit_code);
}

void	free_msh(t_msh *msh)
{
	(void)msh;
}

void	duplicate_env(t_msh *msh, char **envp)
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
		ft_lstadd_back(&msh->dup_env, next_env);
		i++;
	}
}