/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:33:11 by gleal             #+#    #+#             */
/*   Updated: 2021/05/13 01:41:11 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

/*
** checks for invalid input specific to the unset function
** @param:	- [char *] argument/input to be analyzed
**			- [type] param_value
** @return:	[int] true/false
** Line-by-line comments:
** @5-10	in input is invalid we write an error message
*/

int	has_valid_identifier_unset(char *token_str)
{
	char	err_message[100];
	int		check;

	ft_bzero(err_message, 0);
	if (!is_token_valid_unset(token_str, err_message))
	{
		check = 0;
		errno = ENOEXEC;
		write_gen_err_message(err_message);
	}
	else
		check = 1;
	return (check);
}

/*
** checks various types if invalid input
** @param:	- [char *] token_str
**			- [char *] pointer to array of chars
** 			where we will write the message
** @return:	[int] true/false
** Line-by-line comments:
** @6		preventing against "unset $ENVVAR" command
** 			(the correct formatting is unset ENVVAR)
*/

int	is_token_valid_unset(char *token_str, char *err_message)
{
	int		check;

	if (ft_strchr(token_str, '=')
		|| ft_strchr(token_str, '\'')
		|| ft_strchr(token_str, '"')
		|| ft_strchr(token_str, '$'))
	{
		check = 0;
		ft_strcpy(err_message, "unset: `");
		ft_strcat(err_message, token_str);
		ft_strcat(err_message, "': not a valid identifier");
	}
	else
		check = 1;
	return (check);
}

/*
** given the node number to delete it applies the correct lst_del function
(del_first, del_last or del_middle)
** @param:	- [t_list *] linked list head pointer
**			- [int] index of node to be deleted (starts at node 0)
** Line-by-line comments:
** @7-8	protecting against node numbers above the lst size
*/

void	ft_lstdel_node_nbr(t_list **lst, int node_nbr, void (*del)(void*))
{
	if (!lst)
		return ;
	if (node_nbr == 0)
		ft_lstdel_first(lst, del);
	else if (node_nbr == ft_lstsize(*lst) - 1)
		ft_lstdel_last(*lst, del);
	else if (node_nbr >= ft_lstsize(*lst))
		return ;
	else
		ft_lstdel_middle(lst, node_nbr, del);
	return ;
}

/*
** Deletes a node that is neither the first or last in the linked list
(if you're not sure if it can be the first or
last then I suggest using the ft_lstdel_node_nbr)
** @param:	- [t_list *] linked list pointer
**			- [int] linked list number that will be deleted
**			- [void (*f)(void*)] pointer to delete function
*/

void	ft_lstdel_middle(t_list **lst, int node_nbr, void (*del)(void*))
{
	int		cur_node;
	t_list	*tmp;
	t_list	*to_delete;

	cur_node = 0;
	tmp = *lst;
	while (cur_node + 1 < node_nbr)
	{
		tmp = tmp->next;
		cur_node++;
	}
	to_delete = tmp->next;
	tmp->next = to_delete->next;
	del(to_delete->data);
	free(to_delete);
}
