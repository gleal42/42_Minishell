/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:49:30 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 11:41:49 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last_node;

	if (!*lst)
	{
		ft_dlstadd_front(lst, new);
		return ;
	}
	last_node = ft_dlstlast(*lst);
	last_node->next = new;
	new->prev = last_node;
}
