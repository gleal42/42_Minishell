/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:31:58 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/14 10:32:59 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

/*
** Prints environment variable string linked lists one by one
** @param:	- [t_list *] environment variable string linked list
** @return:	[int] exit status 
** Line-by-line comments:
** @3		We want the _ env variable to be /usr/bin/env when the user calls
**			env
*/

int	ft_env(t_list *env)
{
	char	*env_str;

	save_last_token(g_msh.curr_cmd_table);
	while (env)
	{
		env_str = (char *)env->data;
		if (ft_strchr(env_str, '='))
			printf("%s\n", env_str);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
