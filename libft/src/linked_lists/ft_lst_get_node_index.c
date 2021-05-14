/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_node_index.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:47:41 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/12 15:02:10 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_get_node_index(t_list *lst, long long data_to_find)
{
	int	index;

	index = 0;
	while (lst)
	{
		if ((long long)lst->data == data_to_find)
			break ;
		index++;
		lst = lst->next;
	}
	if (!lst)
		index = -1;
	return (index);
}
