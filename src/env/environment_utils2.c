/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:52:25 by gleal             #+#    #+#             */
/*   Updated: 2021/05/01 22:28:28 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Auxiliary function in which we join the home path with the rest of the string
**	example ~/Desktop is now Users/gleal/Desktop
** @param:	- [char **] pointer of function to be updated
**				(pointer of pointer to be freed)
**			- [char **] pointer of function to be updated
**				(pointer of pointer to be freed)
** @return:	[type] return_value
** Line-by-line comments:
** @line-line	comment
*/

void	tilde_join(char **str, char **home_path)
{
	char	*temp;

	temp = ft_strjoin(*home_path, &str[0][1]);
	if (!temp)
		ft_exit(EXIT_FAILURE);
	free(*home_path);
	*home_path = 0;
	free(*str);
	*str = 0;
	*str = temp;
}
