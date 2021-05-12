/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:11:26 by gleal             #+#    #+#             */
/*   Updated: 2021/05/12 09:06:50 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pwd.h"

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
