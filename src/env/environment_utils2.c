/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:04:11 by gleal             #+#    #+#             */
/*   Updated: 2021/05/04 22:18:21 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** In a string of type VAR=VALUE it extracts the VALUE
** @param:	- [char *] string to be analyzed
**			- [type] param_value
** @return:	[char *] string duplicate of value
** Line-by-line comments:
** @11	one more to compensate for the equal sign
*/

char	*get_value_name(char *str)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && !is_delimiter(str[i]) && str[i] != '$'
			&& str[i] != '=')
		i++;
	i++;
	len = ft_strlen(str) - i;
	value = ft_substr(str, i, len);
	if (!value)
		ft_exit(EXIT_FAILURE);
	return (value);
}