/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:11:26 by gleal             #+#    #+#             */
/*   Updated: 2021/05/14 10:41:37 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pwd.h"

/*
** Prints current working directory
** @param:	- [t_list *] environment variable string linked list
** @return:	[int] exit status 
*/

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, 1024) == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
