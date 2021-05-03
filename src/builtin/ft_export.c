/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 19:10:37 by gleal             #+#    #+#             */
/*   Updated: 2021/05/03 23:27:45 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		ft_export(t_list *tokens, t_list **env)
{
	int		status;
	char	*token_str;
	t_list *new_var;

	status = 0;
	if (tokens == 0)
		status = print_all_exported_vars(*env);
	else
	{
		while(tokens)
		{
		//check if variable already exists (update or create new)
			token_str = ft_strdup(((t_token *)tokens->data)->str);
			new_var = ft_lstnew(token_str);
			if (new_var == 0)
				ft_exit(EXIT_FAILURE);
			ft_lstadd_front(env, new_var);
			tokens = tokens->next;
		}
	}
	return (status);
}

int		print_all_exported_vars(t_list *env)
{
	char	*env_str;
	int		i;

	while(env)
	{
		i = -1;
		env_str = (char *)env->data;
		if (ft_strchr(env_str, '='))
		{
			ft_putstr_fd("declare -x ", 1);
			while (env_str[++i] && env_str[(i - 1)] != '=')
				ft_putchar_fd(env_str[i], 1);
			printf("\"%s\"\n", &env_str[i]);
		}
		else
			printf("declare -x %s\n", env_str);
		env = env->next;
	}
	return (0);
}
