/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:20:55 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 11:48:10 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel_last(t_dlist *lst, void (*del)(void*))
{
	t_dlist	*tmp;
	t_dlist	*last_node;

	if (!lst || !lst->next)
		return ;
	last_node = ft_dlstlast(lst);
	tmp = lst->prev;
	tmp->next = 0;
	del(last_node->data);
	free(last_node);
}
