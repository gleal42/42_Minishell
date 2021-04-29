/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:52:25 by gleal             #+#    #+#             */
/*   Updated: 2021/04/29 16:52:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "environment.h"


int     tilde_join(char **str,char **home_path)
{
    char   *temp;

    temp = ft_strjoin(*home_path, &str[0][1]);
	free(*home_path);
	*home_path = 0;
	free(*str);
	*str = 0;
	*str = temp;
    return (0);
}