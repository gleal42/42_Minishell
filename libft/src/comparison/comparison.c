/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:26:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/12 14:30:59 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_equal(int a, int b)
{
	return (a == b);
}

int	is_greater_than_or_equal(int a, int b)
{
	return (a >= b);
}

int	is_greater_than(int a, int b)
{
	return (a > b);
}

int	is_less_than_or_equal(int a, int b)
{
	return (a <= b);
}

int	is_less_than(int a, int b)
{
	return (a < b);
}
