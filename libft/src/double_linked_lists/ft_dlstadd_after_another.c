/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_after_another.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:49:30 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 11:39:07 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_after_another(t_dlist *node, t_dlist *node_to_insert)
{
	node_to_insert->next = node->next;
	node_to_insert->prev = node;
	node->next = node_to_insert;
	if (!node_to_insert->next)
		node_to_insert->next->prev = node_to_insert;
}
