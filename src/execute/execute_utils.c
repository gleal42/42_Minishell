/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:53:43 by gleal             #+#    #+#             */
/*   Updated: 2021/05/10 14:52:16 by dda-silv         ###   ########.fr       */
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
		exit(ft_echo(tokens->next));
	if ((ft_strcmp(first, "env") == 0) && tokens->next == 0)
		exit(ft_env(*env));
	if (ft_strcmp(first, "cd") == 0)
		exit(ft_cd(tokens->next, env));
	if (ft_strcmp(first, "pwd") == 0)
		exit(ft_pwd());
	if (ft_strcmp(first, "export") == 0)
		exit(ft_export(tokens->next, env));
	if (ft_strcmp(first, "unset") == 0)
		exit(ft_unset(tokens->next, env));
	exit(0);
}

pid_t	*init_pids(int nb_cmds)
{
	pid_t	*pids;

	pids = ft_calloc(nb_cmds, sizeof(pid_t));
	if (!pids)
		exit_prog(EXIT_FAILURE);
	return (pids);
}

int	**init_pipes(int nb_cmds)
{
	int	**pipes;
	int	i;

	if (nb_cmds == 1)
		return (0);
	pipes = ft_calloc(nb_cmds, sizeof(int *));
	if (!pipes)
		exit_prog(EXIT_FAILURE);
	i = 0;
	while (i < nb_cmds - 1)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i])
			exit_prog(EXIT_FAILURE);
		if (pipe(pipes[i]) == -1)
			exit_prog(EXIT_FAILURE);
		i++;
	}
	return (pipes);
}

void	check_exit(t_cmd *cmd)
{
	t_token	*tokens;
	char	*first_cmd;

	tokens = cmd->tokens->data;
	first_cmd = tokens->str;
	if (ft_strcmp(first_cmd, "exit") == 0)	
		exit_prog(EXIT_SUCCESS);
}