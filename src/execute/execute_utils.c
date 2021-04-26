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

int		execute_builtin(char **tokens, t_list **env)
{
	if (ft_strcmp(tokens[0], "echo") == 0)
		return (ft_echo(&tokens[1]));
	if ((ft_strcmp(tokens[0], "env") == 0) && tokens[1] == 0)
		return (ft_env(*env));
	if (ft_strcmp(tokens[0], "cd") == 0)
		return (ft_cd(&tokens[1], env));
	return (0);
}
