/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_absolute_path2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:30:45 by gleal             #+#    #+#             */
/*   Updated: 2021/05/13 18:32:06 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_absolute_path.h"

int	has_absolute_path(char *first_token)
{
	int	check;

	if (*first_token == '/')
		check = 1;
	else
		check = 0;
	return (check);
}