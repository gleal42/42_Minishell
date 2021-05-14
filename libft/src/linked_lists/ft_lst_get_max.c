/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_max.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:47:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/14 09:48:35 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_lst_get_max(t_list *lst)
{
	long long	max;

	if (!lst)
		return (INT_MAX);
	max = (long long int)lst->data;
	while (lst)
	{
		if (max < (long long int)lst->data)
			max = (long long int)lst->data;
		lst = lst->next;
	}
	return (max);
}
