/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:57:24 by gleal             #+#    #+#             */
/*   Updated: 2021/05/01 21:11:42y gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Replaces the environment variables with the respective values.
** @param:	- [t_list *]Linked List with struct pointer;
** Line-by-line comments:
** @8-10	tilde expansion;
** @11-12	When using single quotes there is no env var substitution;
*/

void	env_vars(t_list	*tokens, int last_status)
{
	char	**str;
	char	delim;

	while (tokens)
	{
		str = &((t_token *)tokens->data)->str;
		delim = ((t_token *)tokens->data)->delimiter;
		if (delim == ' ' && str[0][0] == '~'
			&& (str[0][1] == '\0' || str[0][1] == '/'))
			replace_tilde_with_home(str);
		if (delim != '\'')
		{
			replace_vars_with_values(str);
			replace_special_params(str, last_status);
		}
		tokens = tokens->next;
	}
}

/*
** Finds dollar signs in tokens and replaces the following with the correct
value
** @param:	- [char *]Tokens (which can be strings with spaces when using
						double quotes) 
** Line-by-line comments:
** @13	replaces the token string with another with the respective value;
*/

void	replace_vars_with_values(char **str)
{
	int		i;
	char	*var;
	char	*value;
	char	*final;

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '$' && (i == 0 || str[0][i - 1] != '\\'))
		{
			var = get_var_name(&str[0][i]);
			value = ft_getenv(var + 1);
			if (value)
			{
				final = replace_midstring(*str, var, value, i);
				free(value);
				free(*str);
				value = 0;
				*str = final;
			}
			free(var);
			var = 0;
		}
		i++;
	}
}

/*
** Replaces the tilde token with the home directory
** @param:	- [char *] token
** Line-by-line comments:
** @11	in the env_vars function the condition we
**		set was having a tilde
**		with a null char or a forward slash after. 
**		So this else condition refers to the
**		forward slash case
*/

void	replace_tilde_with_home(char **str)
{
	char	*home_path;

	home_path = ft_getenv("HOME");
	if (!str[0][1])
	{
		free(*str);
		*str = home_path;
	}
	else
		tilde_join(str, &home_path);
}

/*
** Used at the moment simply to replace $? for the exit status of the previous
function
** @param:	- [char **] pointer to token string in linked list
**			- [int] exit status from last function executed
** Line-by-line comments:
** @5	function that finds the place where we will replace the substring
(iterator as opposed to string pointer);
*/

void	replace_special_params(char **str, int last_status)
{
	int		replace_spot;
	char	*status_string;
	char	*final;

	replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	if (replace_spot != -1)
	{
		status_string = ft_itoa(last_status);
		if (status_string == 0)
			return (ft_exit(EXIT_FAILURE));
		final = replace_midstring(*str, "$?", status_string, replace_spot);
		free(status_string);
		status_string = 0;
		free(*str);
		*str = final;
	}
}
