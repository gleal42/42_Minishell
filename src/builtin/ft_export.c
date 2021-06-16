/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:29:13 by dds               #+#    #+#             */
/*   Updated: 2021/05/24 17:18:28 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_export.h"

/*
** - If no arguments print all environment variables (including unnassigned
** ones(e.g. VAR instead of VAR=10))
** - If there are arguments each argument is a potential environment variable
** to be added to the environment variable linked list
** @param:	- [t_list *] list of tokens in a command
**			- [t_list **] pointer to envp linked list
** @return:	[int] exit status
** Line-by-line comments:
** @16-17	In case the variable already exists we just need to update it in 
**			the list and only if it is assigned: (e.g. If in envp ENVVAR=5
**			export ENVVAR has no effect)
** @20		If the variable doesn't exist we create a new node in the envp
**			linked list
*/

int	ft_export(t_list *tokens, t_list **env)
{
	char	*var;
	char	*token_str;

	if (tokens == 0)
		print_all_exported_vars(*env);
	while (tokens)
	{
		token_str = tokens->data;
		if (!has_valid_identifier_export(token_str))
			return (EXIT_FAILURE);
		if (has_only_one_cmd())
		{
			var = get_var_name(token_str);
			if (is_env_var(var, *env))
			{
				if (ft_strchr(token_str, '='))
					update_env_var_with_token(token_str, var, *env);
			}
			else
				create_environment_var(token_str, env);
			free(var);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

/*
** Prints all the environment variables with the proper formatting and sorted
** in alphabetic order
** @param:	- [t_list *] pointer to envp linked list
** Line-by-line comments:
** @12-18	If variable is assigned (has equal sign) then we need to add double
**			quotes
*/

void	print_all_exported_vars(t_list *env)
{
	t_list	*sorted_env;
	t_list	*tmp;
	char	*env_str;
	int		i;

	sorted_env = get_sorted_env(env);
	tmp = sorted_env;
	while (tmp)
	{
		i = 0;
		env_str = (char *)tmp->data;
		if (ft_strchr(env_str, '='))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			while (env_str[i] != '=')
				ft_putchar_fd(env_str[i++], STDOUT_FILENO);
			printf("=\"%s\"\n", &env_str[++i]);
		}
		else
			printf("declare -x %s\n", env_str);
		tmp = tmp->next;
	}
	ft_lstclear(&sorted_env, ft_lstdel_int);
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

t_list	*get_sorted_env(t_list *env)
{
	t_list	*sorted_env;

	sorted_env = ft_lstdup(env);
	if (!sorted_env)
		quit_program(EXIT_FAILURE);
	ft_lst_sort_str(&sorted_env, ft_strcmp);
	return (sorted_env);
}
