/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:11:52 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/03 10:43:12 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	char	*sav_str;
	char	*sav_to_find;

	if (!(*to_find))
		return (str);
	while (*str)
	{
		sav_str = str;
		sav_to_find = to_find;
		while (*str++ == *to_find++)
		{
			if (*to_find == '\0')
				return (sav_str);
		}
		str = sav_str++;
		to_find = sav_to_find;
	}
	return (0);
}
