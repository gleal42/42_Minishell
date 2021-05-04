/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:53:43 by gleal             #+#    #+#             */
/*   Updated: 2021/05/04 22:51:50 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** Checks if token is one of the mandatory builtin function	
** @param:	- [char *] token to be checked
** @return:	[int] indicates if the token is a builtin or not
*/

int	is_builtin(char *first_token)
{
	if (ft_strcmp(first_token, "echo") == 0)
		return (1);
	if (ft_strcmp(first_token, "env") == 0)
		return (1);
	if (ft_strcmp(first_token, "cd") == 0)
		return (1);
	if (ft_strcmp(first_token, "pwd") == 0)
		return (1);
	if (ft_strcmp(first_token, "export") == 0)
		return (1);
	if (ft_strcmp(first_token, "unset") == 0)
		return (1);
	else
		return (0);
}

/*
** Redirects to builtin functions
** @param:	- [t_list *] list of tokens in a command
**			- [t_list **] pointer to environment variable linked list
** @return:	[int] command return values
** Line-by-line comments:
** @6			we're only asked to deal with env with no arguments
*/

int	execute_builtin(t_list	*tokens, t_list **env)
{
	char	*first;

	first = ((t_token *)tokens->data)->str;
	if (ft_strcmp(first, "echo") == 0)
		return (ft_echo(tokens->next));
	if ((ft_strcmp(first, "env") == 0) && tokens->next == 0)
		return (ft_env(*env));
	if (ft_strcmp(first, "cd") == 0)
		return (ft_cd(tokens->next, env));
	if (ft_strcmp(first, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(first, "export") == 0)
		return (ft_export(tokens->next, env));
	if (ft_strcmp(first, "unset") == 0)
		return (ft_unset(tokens->next, env));
	return (0);
}
