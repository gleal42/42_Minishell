/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:44:56 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 20:02:29 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_max(long long nb, char next_digit, int sign)
{
	int	check;

	check = 0;
	if (nb == LLONG_MAX / 10 && next_digit <= '7' && sign == 1)
		check = 0;
	else if (nb == LLONG_MAX / 10 && next_digit <= '8' && sign == -1)
		check = 0;
	else if (nb >= LLONG_MAX / 10)
		check = 1;
	return (check);
}

long long	ft_atoi(const char *str)
{
	long long	number;
	int			sign;

	number = 0;
	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while ('0' <= *str && *str <= '9')
	{
		if (is_max(number, *str, sign))
			return (0);
		number *= 10;
		number += (int)(*str - '0');
		str++;
	}
	return (sign * number);
}
