/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remainder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 07:41:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 12:04:25 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long double	ft_remainder(long double numer, long double denom)
{
	if (numer < 0)
		numer *= -1;
	return (numer - (denom * (long long)(numer / denom)));
}
