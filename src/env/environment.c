/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:57:24 by gleal             #+#    #+#             */
/*   Updated: 2021/04/26 21:20:00 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "environment.h"

t_list	*dup_env(char **envp)
{
	t_list	*first;
	t_list	*next;

	int		i;

	if (!envp || !envp[0])
		return (NULL);
	first = ft_lstnew(ft_strdup(envp[0]));
	if (!first)
		return (NULL);
	i = 1;
	while (envp[i] != NULL)
	{
		next = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(&first, next);
		i++;
	}
	return (first);
}

int		env_vars(char ***tokens, t_list **env)
{
	int		i;

	i = 0;
	while (tokens[0][i])
	{
		if (tokens[0][i][0] == '$')
			replace_var_with_value(&tokens[0][i], &tokens[0][i][1], *env);
		i++;
	}
	return (0);
}

int		replace_var_with_value(char **cur_token, char *var, t_list *env)
{
	int		i;
	char	*env_str;

	while (env)
	{
		i = 0;
		env_str = (char *)env->data;
		while (var[i] && env_str[i] && (var[i] == env_str[i]))
			i++;
		if (!var[i] && env_str[i] == '=')
		{
			replace_strstr_offset(cur_token, env_str, i + 1);
			return (1);
		}
		env=env->next;
	}
		return (0);
}

int		replace_strstr_offset(char **cur_token, char *env, int start)
{
	char	*value;
	int		len;

	len = ft_strlen(env) - start;
	value = ft_substr(env, start, len);
	free(*cur_token);
	*cur_token = 0;
	*cur_token = value;
	return(0);
}

char	*get_env_value(char *var, t_list *env)
{
	int		i;
	char	*env_str;
	char	*env_value;

	while (env)
	{
		i= 0;
		env_str = (char *)env->data;
		while (var[i] && env_str[i] && (var[i] == env_str[i]))
			i++;
		if (!var[i] && env_str[i] == '=')
		{
			env_value = ft_strdup(&(env_str[i + 1]));
			return (env_value);
		}
		env = env->next;
	}
	return (0);
}
