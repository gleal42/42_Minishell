/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:55:24 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/19 18:02:00 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Line-by-line comments:
** @2		The INT_MIN edge case is not relevant as the number reaching
**			the function convert_to_char() are between -9 and 9
*/

static int	convert_to_char(int nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb + ASCII_OFFSET_NUM);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	n_to_print;
	int		remainder;
	int		ret;

	if (0 <= n && n < 10)
	{
		n_to_print = convert_to_char(n);
		ret = write(fd, &n_to_print, 1);
		return ;
	}
	else if (-10 < n && n < 0)
	{
		ret = write(fd, "-", 1);
		n_to_print = convert_to_char(n);
		ret = write(fd, &n_to_print, 1);
		return ;
	}
	remainder = n % 10;
	ft_putnbr_fd(n / 10, fd);
	n_to_print = convert_to_char(remainder);
	ret = write(fd, &n_to_print, 1);
	return ;
	(void)ret;
}
