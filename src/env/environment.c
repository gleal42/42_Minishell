/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:57:24 by gleal             #+#    #+#             */
/*   Updated: 2021/04/24 15:34:09 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "environment.h"

t_list	*dup_env(char **envp)
{
	t_list	*first;
	t_list	*next;

	int		i;

	if (!envp || !envp[0])
		return (NULL);
	first = ft_lstnew(ft_strdup(envp[0]));
	if (!first)
		return (NULL);
	i = 1;
	while (envp[i] != NULL)
	{
		next = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(&first, next);
		i++;
	}
	return (first);
}
