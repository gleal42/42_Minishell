/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:49:07 by gleal             #+#    #+#             */
/*   Updated: 2021/04/29 17:49:14 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

int		update_directories(char *new_dir, char *old_dir, t_list *env)
{
	update_environment_var("PWD", new_dir, env);
	update_environment_var("OLDPWD", old_dir, env);
	return (0);
}

int		update_environment_var(char *var, char *new_value, t_list *env)
{
	int		i;
	char *cur_env;

	while(env)
	{
		i = 0;
		cur_env = (char *)(env->data);
		while (var[i] && cur_env[i] && (var[i] == cur_env[i]))
			i++;
		if (!var[i] && cur_env[i] == '=')
		{
			replace_env_value(&cur_env, var, new_value);
			return (0);
		}
		env = env->next;
	}
	return (0);
}
int		replace_env_value(char **env_ptr, char	*var_name, char *new_value)
{
	char	*temp;
	char	*final;
	temp = ft_strjoin(var_name, "=");
	final = ft_strjoin(temp, new_value);
	free(*env_ptr);
	*env_ptr = final;
	return (0);
}