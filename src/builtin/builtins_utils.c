/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:49:07 by gleal             #+#    #+#             */
/*   Updated: 2021/04/30 13:51:47y gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	update_directories(char *old_dir, t_list **env)
{
	char	new_dir_temp[1024];
	char	*new_dir;

	if (getcwd(new_dir_temp, 1024) == NULL)
		return (0);
	new_dir = ft_strdup(new_dir_temp);
	update_environment_var("PWD", new_dir, *env);
	update_environment_var("OLDPWD", old_dir, *env);
	free(new_dir);
	new_dir = 0;
	return (0);
}

int	update_environment_var(char *var, char *new_value, t_list *env)
{
	int		i;
	char	*cur_env;

	while (env)
	{
		i = 0;
		cur_env = (char *)(env->data);
		while (var[i] && cur_env[i] && (var[i] == cur_env[i]))
			i++;
		if (!var[i] && cur_env[i] == '=')
		{
			env->data = replace_env_value(&cur_env, var, new_value);
			return (0);
		}
		env = env->next;
	}
	return (0);
}

char	*replace_env_value(char **env_ptr, char	*var_name, char *new_value)
{
	char	*temp;
	char	*final;

	temp = ft_strjoin(var_name, "=");
	final = ft_strjoin(temp, new_value);
	free(temp);
	temp = 0;
	free(*env_ptr);
	*env_ptr = 0;
	return (final);
}
