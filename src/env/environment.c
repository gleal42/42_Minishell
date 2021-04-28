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
		delim = ((t_token *)tokens->data)->delimiter
		;
	/*	if (tokens[0][i][0] == '~' && (tokens[0][i][1] == 0 || tokens[0][i][1] == '/'))
			replace_tilde_with_home(&tokens[0][i], &tokens[0][i][j], *env)*/
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

int		update_token(char **token_before, int *start, char *value, int var_len)
{
	char	*temp;

	temp = update_token_before(*token_before, start, value);
	temp = update_token_after(*token_before, start, temp, var_len);
	free( *token_before);
	*token_before = 0;
	*token_before = temp;
	(*start) += ft_strlen(value) - 1;
	return(0);
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

char	*update_token_after(char *token_before, int *start, char *temp, int var_len)
{
	char	*final;
	char	*after;

	after = ft_substr(token_before, (*start) + var_len + 1, ft_strlen(token_before) - ((*start) + var_len));
	final = ft_strjoin(temp, after);
	free(after);
	after = 0;
	return (final);
}