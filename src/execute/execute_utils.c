/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:53:43 by gleal             #+#    #+#             */
/*   Updated: 2021/04/26 14:59:03 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execute.h"

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

	while ((env))
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

int		is_builtin(char *first_token)
{
	if (ft_strcmp(first_token, "echo") == 0)
		return (1);
	if (ft_strcmp(first_token, "env") == 0)
		return (1);
	if (ft_strcmp(first_token, "cd") == 0)
		return (1);
	else
		return (0);
}

int		execute_builtin(char **tokens, t_list **env)
{
	if (ft_strcmp(tokens[0], "echo") == 0)
		return (ft_echo(&tokens[1]));
	if ((ft_strcmp(tokens[0], "env") == 0) && tokens[1] == 0)
		return (ft_env(*env));
	if (ft_strcmp(tokens[0], "cd") == 0)
		return (ft_cd(&tokens[1], env));
	return (0);
}
