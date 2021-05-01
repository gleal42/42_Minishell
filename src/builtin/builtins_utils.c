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

/*
** Update the PWD and OLDPWD environment variables based the current 
and previous working directories
** @param:	- [char *] previous working directory
**			- [t_list *] environment variable string linked list
** @return:	[int] signs success or failure of the function
** Line-by-line comments:
** @4	allowed function that fills buffer with null terminated string of 
current working directory;
*/

int	update_directories(char *old_dir, t_list **env)
{
	char	new_dir_temp[1024];
	char	*new_dir;

	if (getcwd(new_dir_temp, 1024) == NULL)
		return (-1);
	new_dir = ft_strdup(new_dir_temp);
	if (!new_dir)
		ft_exit(EXIT_FAILURE);
	update_environment_var("PWD", new_dir, *env);
	update_environment_var("OLDPWD", old_dir, *env);
	free(new_dir);
	new_dir = 0;
	return (0);
}

/*
** Auxiliary function that updated the environment variable string
with a value we define
** @param:	- [char *] variable to look for in the env var linked list
**			- [char *] new value that will replace the current string
			- [t_list *] environment variable string linked list
** @return: [int]	indicates if the substitution took place;
** Line-by-line comments:
** @line-line	comment
*/

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
			return (1);
		}
		env = env->next;
	}
	return (0);
}

/*
** Joins the variable name with a equal sign followed by the value
** @param:	- [char **] pointer to environment variable string to be
updated
**			- [char *] name of variable
			- [char *] updated value string;
** @return:	[char *] updated string to be addded to linked list
*/

char	*replace_env_value(char **env_ptr, char	*var_name, char *new_value)
{
	char	*temp;
	char	*final;

	temp = ft_strjoin(var_name, "=");
	if (!temp)
		ft_exit(EXIT_FAILURE);
	final = ft_strjoin(temp, new_value);
	if (!final)
		ft_exit(EXIT_FAILURE);
	free(temp);
	temp = 0;
	free(*env_ptr);
	*env_ptr = 0;
	return (final);
}
