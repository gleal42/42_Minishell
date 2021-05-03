/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:19:39 by gleal             #+#    #+#             */
/*   Updated: 2021/05/03 16:12:23 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** prints environment variable string linked lists one by one
** @param:	- [t_list *] environment variable string linked list
** @return:	[int] exit status 
*/

int	ft_env(t_list *env)
{
	while (env)
	{
		ft_putstr_fd((char *)env->data, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return (0);
}
