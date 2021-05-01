/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:17:53 by gleal             #+#    #+#             */
/*   Updated: 2021/05/01 21:58:55 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Function goes through the environment variable string linked list and looks
for a match with the potential variable
** @param:	- [char *] Potential variable that we are testing.
**			- [t_list *] environment variable string linked list
** @return:	[int] 1 if true
** Line-by-line comments:
** @11-13	In case the token is between double quotes it can end in a space
*/

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
			return (1);
		env = env->next;
	}
	return (0);
}

/*
** Auxiliary function to extract the potential variable from a string with
dollar sign before a word.
** @param:	- [char *] string from which we will extract the var name
** @return:	[char *] var name
*/

char	*get_var_name(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] && !is_delimiter(str[i]) && str[i] != '$')
		i++;
	var = ft_substr(str, 0, i);
	if (!var)
		ft_exit(EXIT_FAILURE);
	return (var);
}

/*
** Auxiliary function to replace var with value (separate the token in 3 parts
1 - before the dollar sign
2 - value
3 - after dollar sign and environment variable
** @param:	- [char *] pointer to token string
**			- [int *] pointer to token iterator to ensure 
			multiple substitutions
			- [char *]environment variable value
			- [int]string length of environment variable string
** @return:	[type] return_value
** Line-by-line comments:
** @line-line	comment
*/

void	update_token(char **token_before, int *start, char *value, int var_len)
{
	char	*temp;

	temp = update_token_before(*token_before, start, value);
	temp = update_token_after(*token_before, start, &temp, var_len);
	free(*token_before);
	*token_before = 0;
	*token_before = temp;
	(*start) += ft_strlen(value) - 1;
}

char	*update_token_before(char *token_before, int *start, char *value)
{
	char	*before;
	char	*temp;

	before = ft_substr(token_before, 0, *start);
	if (!before)
		ft_exit(EXIT_FAILURE);
	temp = ft_strjoin(before, value);
	if (!temp)
		ft_exit(EXIT_FAILURE);
	free(before);
	before = 0;
	return (temp);
}

char	*update_token_after(char *token_before, int *start,
						char **temp, int var_len)
{
	char	*final;
	char	*after;

	after = ft_substr(token_before, (*start) + var_len + 1,
			ft_strlen(token_before) - ((*start) + var_len));
	if (!after)
		ft_exit(EXIT_FAILURE);
	final = ft_strjoin(*temp, after);
	if (!final)
		ft_exit(EXIT_FAILURE);
	free(after);
	free(*temp);
	after = 0;
	*temp = 0;
	return (final);
}
