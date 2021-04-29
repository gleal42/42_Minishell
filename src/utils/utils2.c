/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:05:29 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/29 08:51:59 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils2.h"

void	init_minishell(t_msh *msh, char **envp)
{
	ft_bzero(msh, sizeof(msh));
	duplicate_env(&msh->dup_envp, envp);
	if (!isatty(STDIN_FILENO))
		ft_exit(EXIT_FAILURE);
	init_termcaps(&msh->termcaps);
}

void	ft_exit(int exit_code)
{
	free_msh();
	turn_on_canonical_mode(&g_msh.termcaps);
	exit(exit_code);
}

void	free_msh(void)
{
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
