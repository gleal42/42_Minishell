/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 07:52:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 11:27:25 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_sqrt(long long nb)
{
	long long	tmp;
	long long	i;

	tmp = nb;
	i = 1;
	while (tmp - i > 0)
	{
		tmp = (tmp + i) / 2;
		i = nb / tmp;
	}
	if (tmp * tmp == nb)
		return (tmp);
	else
		return (0);
}
