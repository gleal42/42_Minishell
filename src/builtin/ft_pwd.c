/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:11:26 by gleal             #+#    #+#             */
/*   Updated: 2021/05/24 17:19:34 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pwd.h"

/*
** Prints current working directory
** @return:	[int] exit status 
*/

int	ft_pwd(void)
{
	char	pwd[MAX_PATH];

	if (getcwd(pwd, MAX_PATH) == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
