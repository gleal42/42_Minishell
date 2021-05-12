/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:17:53 by gleal             #+#    #+#             */
/*   Updated: 2021/05/12 09:18:04 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_utils.h"

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
			&& (env_str[i] == '=' || env_str[i] == '\0'))
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
	if (str[i] == '$')
		i++;
	while (str[i] && !is_delimiter(str[i]) && str[i] != '$'
		&& str[i] != '=')
		i++;
	var = ft_substr(str, 0, i);
	if (!var)
		exit_prog(EXIT_FAILURE);
	return (var);
}

/*
** Auxiliary function to find the iterator in which a particular substring
exist in a string (alternative to strnstr)
** @param:	- [char *] string to be searched
**			- [char *] substring to be found
** @return:	[int] substring position as iterator (negative value if non_existent)
*/

int	ft_strnstr_iterator(char *haystack, char *needle, size_t len)
{
	size_t	little_len;
	int		iterator;

	iterator = 0;
	little_len = ft_strlen(needle);
	if (little_len == 0)
		return (-1);
	if (len == 0)
		return (-1);
	while (haystack[iterator] && (int)(little_len <= len - iterator))
	{
		if (!ft_strncmp(&haystack[iterator], (char *)needle, little_len))
			return (iterator);
		iterator++;
	}
	return (-1);
}

/*
** Replaces substring
** @param:	- [char *] string before substitution
**			- [char *] substring that will be replaced
**			- [char *] substring that will replace
**			- [char *] iterator that indicated place in original string where
substitution should take place
** @return:	[char *] string after substitution
*/

char	*replace_midstring(char *original, char *old_substr,
char *new_substr, int replace_i)
{
	char	*final;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(original) - ft_strlen(old_substr) + ft_strlen(new_substr);
	final = ft_calloc(len + 1, sizeof(char));
	if (final == 0)
		exit_prog(EXIT_FAILURE);
	while (*original)
	{
		if (i == replace_i)
		{
			while (new_substr && *new_substr)
				final[i++] = *(new_substr++);
			original += ft_strlen(old_substr);
		}
		else
			final[i++] = *(original++);
	}
	final[i] = '\0';
	return (final);
}

/*
** Auxiliary function in which we join the home path with the rest of the string
**	example ~/Desktop is now Users/gleal/Desktop
** @param:	- [char **] pointer of function to be updated
**				(pointer of pointer to be freed)
**			- [char **] pointer of function to be updated
**				(pointer of pointer to be freed)
** @return:	[type] return_value
** Line-by-line comments:
** @line-line	comment
*/

void	tilde_join(char **str, char **home_path)
{
	char	*temp;

	temp = ft_strjoin(*home_path, &str[0][1]);
	if (!temp)
		exit_prog(EXIT_FAILURE);
	free(*home_path);
	*home_path = 0;
	free(*str);
	*str = 0;
	*str = temp;
}
