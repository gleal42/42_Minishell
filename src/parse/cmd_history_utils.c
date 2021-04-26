/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:39:11 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/26 19:03:26 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_history_utils.h"

int	ft_putint(int c)
{
	return (write(1, &c, 1));
}

void	get_cursor_position(int *col, int *row, t_termcaps *termcaps)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*row = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += get_len_int(temp) - 1;
		}
		i++;
	}
	(void)termcaps;
}
// {
// 	int		a;
// 	int		i;
// 	// char	*buf;
// 	char	buf[255];
// 	int		ret;
// 	int		temp;

// 	// buf = malloc(termcaps->resolution * sizeof(char));
// 	// if (!buf)
// 	// 	exit(EXIT_FAILURE);
// 	// *col = 0;
// 	// *row = 0;
// 	write(0, "\033[6n", 4);  //report cursor location
// 	ret = read(0, buf, 255);
// 	// write(STDOUT_FILENO, "\033[6n", 4);  //report cursor location
// 	// ret = read(STDIN_FILENO, buf, termcaps->resolution - 1);
// 	buf[ret] = '\0';
// 	// printf("Ret: \"%d\"\n", ret);
// 	// printf("Buf: \"%s\"\n", buf);
// 	a = 0;
// 	i = 0;
// 	// printf("Buf: \"%s\"\n", buf);
// 	while (buf[i])
// 	{
// 		if (ft_isdigit(buf[i]))
// 		{
// 			// if (*col == 0 && *row == 0)
// 			if (a == 0)
// 				*row = ft_atoi(&buf[i]) - 1;
// 			else
// 			{
// 				temp = ft_atoi(&buf[i]);
// 				*col = temp - 1;
// 			}
// 			a++;
// 			i += get_len_int(temp) - 1;
// 		}
// 		i++;
// 	}
// 	// free(buf);
// 	(void)termcaps;
// }
