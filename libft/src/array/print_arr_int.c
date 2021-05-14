/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 21:18:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 21:24:10 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_arr_int(int *arr, int len)
{
	int	i;

	i = 0;
	printf("[");
	while (i < len - 1)
		printf("%d, ", arr[i++]);
	printf("%d]\n", arr[i]);
}
