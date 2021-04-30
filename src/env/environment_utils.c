/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:17:53 by gleal             #+#    #+#             */
/*   Updated: 2021/04/30 17:48:01 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	is_env_var(char *potential_var, t_list *env)
{
	int		i;
	char	*env_str;

	while (env)
	{
		i = 0;
		env_str = (char *)env->data;
		while (potential_var[i] && env_str[i]
			&& (potential_var[i] == env_str[i]))
			i++;
		if ((potential_var[i] == 0 || ft_isspace(potential_var[i]))
			&& env_str[i] == '=')
			return (i);
		env = env->next;
	}
	return (0);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] && !is_delimiter(str[i]) && str[i] != '$')
		i++;
	var = ft_substr(str, 0, i);
	return (var);
}

int	update_token(char **token_before, int *start, char *value, int var_len)
{
	char	*temp;

	temp = update_token_before(*token_before, start, value);
	temp = update_token_after(*token_before, start, temp, var_len);
	free(*token_before);
	*token_before = 0;
	*token_before = temp;
	(*start) += ft_strlen(value) - 1;
	return (0);
}

char	*update_token_before(char *token_before, int *start, char *value)
{
	char	*before;
	char	*temp;

	before = ft_substr(token_before, 0, *start);
	temp = ft_strjoin(before, value);
	free(before);
	before = 0;
	return (temp);
}

char	*update_token_after(char *token_before, int *start,
						char *temp, int var_len)
{
	char	*final;
	char	*after;

	after = ft_substr(token_before, (*start) + var_len + 1,
			ft_strlen(token_before) - ((*start) + var_len));
	final = ft_strjoin(temp, after);
	free(after);
	after = 0;
	return (final);
}
