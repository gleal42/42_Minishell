/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:57:24 by gleal             #+#    #+#             */
/*   Updated: 2021/04/28 19:14:02 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "environment.h"

int		env_vars(t_list	*tokens)
{
	char	**str;
	char	delim;
	while (tokens)
	{
		str = &((t_token *)tokens->data)->str;
		delim = ((t_token *)tokens->data)->delimiter;
		if (delim == ' ' && str[0][0] == '~' && (str[0][1] == '\0' || str[0][1] == '/'))
			replace_tilde_with_home(str);
		if (delim != '\'')
			replace_vars_with_values(str);
		tokens = tokens->next;
	}
	return (0);
}

int		replace_vars_with_values(char **str)
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
	return (0);
}

int		replace_tilde_with_home(char **str)
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
	return (0);
}