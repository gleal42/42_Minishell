/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 20:16:20 by gleal             #+#    #+#             */
/*   Updated: 2021/04/26 22:33:38 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

int		ft_echo(t_list	*tokens)
{
	int		i;
	int		lb;
	int		flag_time;
	char	*arg;
	char	delim;

	flag_time = 1;
	lb = 1;
	i = 0;
	while (tokens)
	{
		arg = ((t_token *)tokens->data)->str;
		delim = ((t_token *)tokens->data)->delimiter;
		if (flag_time && arg[0] == '-' && has_repeated_char_in_str('n', arg, 1))
		{
			lb = 0;
		}
		else
		{
			if (!flag_time)
				ft_putchar_fd(' ', 1);
			flag_time = 0;
			ft_putstr_fd(arg, 1);
		}
		tokens = tokens->next;
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
