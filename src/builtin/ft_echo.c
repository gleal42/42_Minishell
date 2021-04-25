/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 20:16:20 by gleal             #+#    #+#             */
/*   Updated: 2021/04/25 21:39:46 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

int		ft_echo(char **args)
{
	int		i;
	int		lb;
	int		flag_time;

	flag_time = 1;
	lb = 1;
	i = 0;
	while (args[i])
	{
		if (flag_time && args[i][0] == '-' && has_repeated_char_in_str('n', args[i], 1))
		{
			lb = 0;
		}
		else
		{
			if (!flag_time)
				ft_putchar_fd(' ', 1);
			flag_time = 0;
			ft_putstr_fd(args[i], 1);
		}
		i++;
	}
	if (lb)
		ft_putchar_fd('\n', 1);
	return (0);
}

int		has_repeated_char_in_str(char repeat_chr, char *str, unsigned int start)
{
	unsigned int	i;
	i = start;
	while (str[i])
	{
		if (str[i] != repeat_chr)
			return (0);
		i++;
	}
	return (1);
}
