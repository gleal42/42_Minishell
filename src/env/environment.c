/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:57:24 by gleal             #+#    #+#             */
/*   Updated: 2021/04/27 22:37:47 by gleal            ###   ########.fr       */
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
	/*	if (tokens[0][i][0] == '~' && (tokens[0][i][1] == 0 || tokens[0][i][1] == '/'))
			replace_tilde_with_home(&tokens[0][i], &tokens[0][i][j], *env)*/
		replace_vars_with_values(&tokens[0][i], *env);
		i++;
	}
	return (0);
}

int		replace_vars_with_values(char **token, t_list *env)
{
	int		i;
	int		j;	
	char	*env_str;

		while (env)
		{
			env_str = (char *)env->data;
			i = 0;
			while (token[0][i])
			{
				if (token[0][i] == '$')
				{
					j = 0;
					i++;
					while (token[0][i + j] && env_str[j] && (token[0][i + j] == env_str[j]))
						j++;
					if (env_str[j] == '=')
					{
						i += update_midtoken(token, env_str, i, j + 1);
					}
					else
						i--;
				}
				i++;
			}
			env=env->next;
		}
	return (0);
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
