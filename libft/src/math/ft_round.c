/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:45:02 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 11:22:51 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_round(long double nb)
{
	long long	ret;

	if (nb >= 0)
		ret = (long long)(nb + 0.5);
	else
		ret = (long long)(nb - 0.5);
	return (ret);
}
