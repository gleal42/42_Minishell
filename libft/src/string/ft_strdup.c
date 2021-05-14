/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:46:57 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 12:00:55 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*cpy;

	if (!s)
	{
		cpy = malloc(1);
		if (!cpy)
			return (0);
		*cpy = 0;
		return (cpy);
	}
	s_len = ft_strlen(s) + 1;
	cpy = malloc(s_len * sizeof(char));
	if (!cpy)
		return (0);
	ft_strcpy(cpy, s);
	return (cpy);
}
