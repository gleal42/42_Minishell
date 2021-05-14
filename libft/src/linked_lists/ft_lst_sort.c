/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:03:47 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/11 16:25:13 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst_sort.h"

/*
** Sort a linked list (merge sort implementation)
** @param:	- [t_list **] head of the linked list
**			- [int *] ptr to function that compares the data
** Line-by-line comments:
** @6-7		Base case
*/

void	ft_lst_sort(t_list **lst, int (*op)(int, int))
{
	t_list	*head;
	t_list	*a;
	t_list	*b;

	head = *lst;
	if (head == NULL || head->next == NULL)
		return ;
	split_list(head, &a, &b);
	ft_lst_sort(&a, op);
	ft_lst_sort(&b, op);
	*lst = merge_sort(a, b, op);
}

/*
** Splits the list in half
** @param:	- [t_list *] head of the list
**			- [t_list **] where we'll be attaching the first half
**			- [t_list **] where we'll be attaching the second half
** Line-by-line comments:
** @4		Slow moves twice as slowly as fast
** @6-14	When fast reached the end, we know that slow is half way into the
**			list
** @16		'Slow' is right before the midpoint of the list so its 'next'
**			value points to the beginning of the second half of the list
** @17		Disconnecting the two halves
*/

static void	split_list(t_list *head, t_list **first_half, t_list **second_half)
{
	t_list	*slow;
	t_list	*fast;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*first_half = head;
	*second_half = slow->next;
	slow->next = NULL;
}

/*
** Recursively merge the halves of lists
** @param:	- [t_list *] first half
** 			- [t_list *] second half
**			- [int *] ptr to function that compares the data
** @return:	[t_list *] linked list result
** Line-by-line comments:
** @4-11	Base case
*/

static t_list	*merge_sort(t_list *a, t_list *b, int (*op)(int, int))
{
	t_list	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (op((long int)a->data, (long int)b->data))
	{
		result = a;
		result->next = merge_sort(a->next, b, op);
	}
	else
	{
		result = b;
		result->next = merge_sort(a, b->next, op);
	}
	return (result);
}

int	ascending(int a, int b)
{
	return (a < b);
}

int	descending(int a, int b)
{
	return (a > b);
}
