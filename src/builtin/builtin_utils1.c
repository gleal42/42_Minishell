/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:10:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 11:42:17 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

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
	char	new_dir[1024];

	if (getcwd(new_dir, 1024) == NULL)
		return (1);
	update_environment_var("PWD", new_dir, *env);
	update_environment_var("OLDPWD", old_dir, *env);
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
		quit_program(EXIT_FAILURE);
	final = ft_strjoin(temp, new_value);
	if (!final)
		quit_program(EXIT_FAILURE);
	free(temp);
	temp = 0;
	free(*env_ptr);
	*env_ptr = 0;
	return (final);
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
		if (!var[i] && (cur_env[i] == '=' || cur_env[i] == '\0' ))
		{
			env->data = replace_env_value(&cur_env, var, new_value);
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	has_valid_identifier_export(char *token_str)
{
	char	err_message[100];
	int		check;

	ft_bzero(err_message, 0);
	if (!is_token_valid_export(token_str, err_message))
	{
		check = 0;
		errno = ENOEXEC;
		write_gen_err_message(err_message);
	}
	else
		check = 1;
	return (check);
}

int	is_token_valid_export(char *token_str, char *err_message)
{
	int		check;

	if ((token_str[0] == '=')
		|| ft_strchr(token_str, '\'')
		|| ft_strchr(token_str, '"'))
	{
		check = 0;
		ft_strcpy(err_message, "export: `");
		ft_strcat(err_message, token_str);
		ft_strcat(err_message, "': not a valid identifier");
	}
	else
		check = 1;
	return (check);
}
