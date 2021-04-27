/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:17:53 by gleal             #+#    #+#             */
/*   Updated: 2021/04/27 22:35:15 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "environment.h"

int		is_env_var(char *potential_var, t_list *env)
{
	int		i;
	char	*env_str;

	while (env)
	{
		i = 0;
		env_str = (char *)env->data;
		while (potential_var[i] && env_str[i] && (potential_var[i] == env_str[i]))
			i++;
		if ((potential_var[i] == 0 || ft_isspace(potential_var[i])) && env_str[i] == '=')
			return (i);
		env = env->next;
	}
	return (0);
}

int		update_midtoken(char **outdated, char *src, int start, int old_word_len)
{
	char	*before;
	char	*value;
	char	*after;
	char	*final;

	before = ft_substr(*outdated, 0, start - 1);
	after = ft_substr(*outdated, start - 1 + old_word_len, ft_strlen(*outdated) - (start - 1 + old_word_len));
	value = ft_substr(src, old_word_len, ft_strlen(src) - old_word_len);
	final = ft_strjoin_three(before, value, after);
	free(before);
	free(value);
	free(after);
	before = 0;
	value = 0;
	after = 0;
	free(*outdated);
	*outdated = 0;
	*outdated = final;
	return(ft_strlen(src) - old_word_len - 1);
}
char	*ft_strjoin_three(char *first_substr, char *second_substr, char *third_substr)
{
	char	*temp;
	char	*final;

	temp = ft_strjoin(first_substr, second_substr);
	final = ft_strjoin(temp, third_substr);
	free(temp);
	return (final);
}
