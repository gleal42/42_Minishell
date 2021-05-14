/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_absolute_path2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:30:45 by gleal             #+#    #+#             */
/*   Updated: 2021/05/14 04:07:51 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_absolute_path.h"

/*
** auxiliary function to determine if path is absolute
** @param:	- [char *] path to be analyzed
** @return:	[int] 1 if true
** Line-by-line comments:
*/

int	has_absolute_path(char *first_token)
{
	int	check;

	if (*first_token == '/')
		check = 1;
	else
		check = 0;
	return (check);
}
