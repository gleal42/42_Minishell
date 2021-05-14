/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:51:03 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/11 16:28:15 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Duplicates a linked list
** @param:	- [t_list *] linked list to duplicate
** @return:	[t_list *] duplicate
*/

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*new_lst;
	t_list	*tmp;

	new_lst = 0;
	while (lst)
	{
		tmp = ft_lstnew(lst->data);
		if (!tmp)
			return (0);
		ft_lstadd_back(&new_lst, tmp);
		lst = lst->next;
	}
	return (new_lst);
}
