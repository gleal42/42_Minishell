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

void	env_vars(t_list	*tokens)
{
	char	**str;
	char	delim;

	while (tokens)
	{
		str = &((t_token *)tokens->data)->str;
		delim = ((t_token *)tokens->data)->delimiter;
		if (delim == ' ' && str[0][0] == '~' && (str[0][1] == '\0' ||
		str[0][1] == '/'))
			replace_tilde_with_home(str);
		if (delim != '\'')
			replace_vars_with_values(str);
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

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '$')
		{
			var = get_var_name(&str[0][i + 1]);
			value = ft_getenv(var);
			if (value)
				update_token(str, &i, value, ft_strlen(var));
			free(var);
			free(value);
			var = 0;
			value = 0;
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
		*str = 0;
		*str = home_path;
	}
	else
		tilde_join(str, &home_path);
}
