/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:31:59 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 11:35:22 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ultoa(unsigned long long n)
{
	char	*str;
	size_t	size_nbr;

	size_nbr = get_len_uint(n);
	str = ft_calloc(size_nbr + 1, sizeof(char));
	if (!str)
		return (0);
	str += size_nbr - 1;
	while (size_nbr--)
	{
		*str-- = n % 10 + ASCII_OFFSET_NUM;
		n /= 10;
	}
	return (++str);
}
