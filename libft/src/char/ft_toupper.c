/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:37:38 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 12:03:46 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define UPPERCASE_OFFSET 32

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - UPPERCASE_OFFSET);
	else
		return (c);
}
