/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:46:03 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/10 14:52:16 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_program_utils.h"

int	has_relative_path(char *first_token)
{
	int	check;

	if (*first_token == '.' || *first_token == '/')
		check = 1;
	else
		check = 0;
	return (check);
}

char	*get_absolute_path(char *program_name)
{
	char		*absolute_path;
	char		**path_env_split;

	path_env_split = get_path_env_split();
	if (!path_env_split)
	{
		absolute_path = ft_strdup(program_name);
		if (!absolute_path)
			exit_prog(EXIT_FAILURE);
		return (absolute_path);
	}
	absolute_path = get_correct_path(program_name, path_env_split);
	free_arr((void **)path_env_split);
	return (absolute_path);
}

char	**get_path_env_split(void)
{
	char		*path_env;
	char		**path_env_split;

	path_env = ft_getenv("PATH");
	if (!path_env)
		return (0);
	path_env_split = ft_split(path_env, ":");
	free(path_env);
	if (!path_env_split)
		exit_prog(EXIT_FAILURE);
	add_slash(&path_env_split);
	return (path_env_split);
}

char	*get_correct_path(char *program_name, char **path_env_split)
{
	char		*absolute_path;
	struct stat	statbuf;
	int			i;

	i = 0;
	while (path_env_split[i])
	{
		absolute_path = ft_strjoin(path_env_split[i], program_name);
		if (!absolute_path)
			exit_prog(EXIT_FAILURE);
		if (stat(absolute_path, &statbuf) == EXIT_SUCCESS)
			break ;
		free(absolute_path);
		i++;
	}
	if (!path_env_split[i])
	{
		absolute_path = ft_strdup(program_name);
		if (!absolute_path)
			exit_prog(EXIT_FAILURE);
	}
	return (absolute_path);
}

void	add_slash(char ***path_env_split)
{
	int		i;
	char	*tmp;
	int		len;
	char	*path;

	i = 0;
	while ((*path_env_split)[i])
	{
		path = (*path_env_split)[i];
		len = ft_strlen(path);
		if (path[len - 1] != '/')
		{
			tmp = ft_strjoin(path, "/");
			free(path);
			(*path_env_split)[i] = tmp;
		}
		i++;
	}
}
