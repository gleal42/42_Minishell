/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_centile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:48:03 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/16 12:05:06 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_lst_get_centile(t_list *lst, int ctl_picked)
{
	t_list		*dup;
	t_list		*tmp;
	int			centile;
	long long	ret;

	if (1 < ctl_picked && ctl_picked < 10)
		return (0);
	dup = ft_lstdup(lst);
	centile = ft_lstsize(dup) * ctl_picked / 100;
	ft_lst_sort(&dup, ascending);
	tmp = dup;
	while (centile--)
		tmp = tmp->next;
	ret = (long long)tmp->data;
	ft_lstclear(&dup, ft_lstdel_int);
	return (ret);
}
