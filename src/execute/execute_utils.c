/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:53:43 by gleal             #+#    #+#             */
/*   Updated: 2021/04/26 21:06:56 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execute.h"

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

int		execute_builtin(t_list	*tokens, t_list **env)
{
	char	*first;

	first = ((t_token *)tokens->data)->str;
	if (ft_strcmp(first, "echo") == 0)
		return (ft_echo(tokens->next));
	if ((ft_strcmp(first, "env") == 0) && tokens->next == 0)
		return (ft_env(*env));
	if (ft_strcmp(first, "cd") == 0)
		return (ft_cd(tokens->next, env));
	return (0);
}