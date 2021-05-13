/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 19:41:19 by gleal             #+#    #+#             */
/*   Updated: 2021/05/13 19:45:19 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_utils.h"

int	is_in_path_env(char *last_cmd_str)
{
	char	*last_cmd_dir;
	char	**path_env_split;
	int	i;
	int	result;

	result = 0;
	path_env_split = get_path_env_split();
	if (!path_env_split)
		return (0);
	last_cmd_dir = get_path_dir(last_cmd_str);
	if (last_cmd_dir == 0)
		return (0);
	i = 0;
	while(path_env_split[i])
	{
		if (ft_strcmp(last_cmd_dir, path_env_split[i]) == 0)
		{
			result  = 1;
			break ;
		}
		i++;
	}
	free (last_cmd_dir);
	free_arr((void **)path_env_split);
	return (result);
}