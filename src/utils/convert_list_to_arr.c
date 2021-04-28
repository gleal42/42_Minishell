/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:32:02 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 12:22:28 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** Converts a linked list to a NULL-terminated array of strings
** @param:	- [t_list *] list with string as data
**			- [type] param_value
** @return:	[char **] NULL-terminated array of strings
** Line-by-line comments:
** @12&15	We don't want to free the strings within each node of the list
**			because we'll keep their address in strs. The ft_lstdel_int does
**			nothing to the data within each node
*/

char	**convert_list_to_arr(t_list **lst)
{
	t_list	*tmp;
	char	**strs;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(*lst);
	strs = ft_calloc(len + 1, sizeof(char *));
	tmp = *lst;
	while (i < len)
	{
		strs[i++] = (char *)tmp->data;
		tmp = tmp->next;
	}
	ft_lstclear(lst, ft_lstdel_int);
	return (strs);
}
