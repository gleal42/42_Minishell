/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:11:26 by gleal             #+#    #+#             */
/*   Updated: 2021/05/03 18:19:37 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** prints current working directory
** @param:	- [t_list *] environment variable string linked list
** @return:	[int] exit status 
*/

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, 1024) == NULL)
		return (1);
	printf("%s\n", pwd);
	return (0);
}
