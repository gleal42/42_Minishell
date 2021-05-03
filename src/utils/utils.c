/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/03 17:28:25 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	write_prompt(void)
{
	ft_putstr(GREEN);
	ft_putstr("msh$ ");
	ft_putstr(RESET);
}

void	write_gen_err_message(char *err_message)
{
	ft_putstr("msh: ");
	ft_putstr(err_message);
	ft_putstr("\n");
}

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
