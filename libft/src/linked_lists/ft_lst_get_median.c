/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_median.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:48:03 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/15 12:18:44 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_lst_get_median(t_list *lst)
{
	t_list		*dup;
	t_list		*tmp;
	int			half_size;
	long long	median;

	dup = ft_lstdup(lst);
	half_size = ft_lstsize(dup) / 2;
	ft_lst_sort(&dup, ascending);
	tmp = dup;
	while (half_size--)
		tmp = tmp->next;
	median = (long long)tmp->data;
	ft_lstclear(&dup, ft_lstdel_int);
	return (median);
}
