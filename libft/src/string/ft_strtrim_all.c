/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:31:13 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/04 17:13:29 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtrim_all.h"

char	*ft_strtrim_all(const char *s1, const char *set)
{
	char	*new_str;
	char	**split;
	size_t	size_new_str;

	if (!s1)
		return (0);
	split = ft_split((char *)s1, (char *)set);
	if (!split)
		return (0);
	size_new_str = get_length(split);
	if (size_new_str == 0)
		return (ft_strdup(""));
	new_str = ft_calloc(size_new_str + 1, sizeof(char));
	if (!new_str)
		return (0);
	concat_all(new_str, split);
	free_arr((void **)split);
	return (new_str);
}

static size_t	get_length(char **strs)
{
	size_t	len;

	len = 0;
	while (*strs)
	{
		len += ft_strlen(*strs);
		strs++;
	}
	return (len);
}

static void	concat_all(char *dest, char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_strcat(dest, strs[i]);
		i++;
	}
}
