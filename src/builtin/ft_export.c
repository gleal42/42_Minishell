/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 19:10:37 by gleal             #+#    #+#             */
/*   Updated: 2021/05/04 19:26:42y gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_export.h"

/*
** - if no arguments print all environment variables
** (including unnassigned ones(e.g. VAR instead of VAR=10))
** - if there are arguments each argument is a potential
** environment variable to be added to the environment
** variable linked list
** @param:	- [t_list *] list of tokens in a command
**			- [t_list **] pointer to envp linked list
** @return:	[int] exit status
** Line-by-line comments:
** @18-19	in case the variable already exists we
** 			just need to update it in the list
** @20-21	if the variable doesn't exist we create
**			a new node in the envp linked list
*/

int	ft_export(t_list *tokens, t_list **env)
{
	char	*var;
	char	*token_str;

	if (tokens == 0)
		print_all_exported_vars(*env);
	else
	{
		while (tokens)
		{
			token_str = ((t_token *)tokens->data)->str;
			if (!has_valid_identifier_export(token_str))
				return (1);
			var = get_var_name(token_str);
			if (is_env_var(var, *env))
			{
				if (ft_strchr(token_str, '='))
					update_env_var_with_token(token_str, var, *env);
			}
			else
				create_environment_var(token_str, env);
			free(var);
			tokens = tokens->next;
		}
	}
	return (0);
}

/*
** Prints all the environment variables with the proper formatting
** @param:	- [t_list **] pointer to envp linked list
** Line-by-line comments:
** @8-14	if variable is assigned (has equal sign) then we need
**			to add double quotes
*/

void	print_all_exported_vars(t_list *env)
{
	char	*env_str;
	int		i;

	while (env)
	{
		i = -1;
		env_str = (char *)env->data;
		if (ft_strchr(env_str, '='))
		{
			ft_putstr_fd("declare -x ", 1);
			while (env_str[++i] && env_str[(i - 1)] != '=')
				ft_putchar_fd(env_str[i], 1);
			printf("\"%s\"\n", &env_str[i]);
		}
		else
			printf("declare -x %s\n", env_str);
		env = env->next;
	}
	return ;
}

void	update_env_var_with_token(char *token_str, char *var, t_list *env)
{
	char	*value;

	value = get_value_name(token_str);
	update_environment_var(var, value, env);
	free(value);
}

void	create_environment_var(char *token_str, t_list **env)
{
	t_list	*new_var;
	char	*new_var_str;

	new_var_str = ft_strdup(token_str);
	if (new_var_str == 0)
		quit_program(EXIT_FAILURE);
	new_var = ft_lstnew(new_var_str);
	if (new_var == 0)
		quit_program(EXIT_FAILURE);
	ft_lstadd_front(env, new_var);
}
