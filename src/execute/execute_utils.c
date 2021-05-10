/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:53:43 by gleal             #+#    #+#             */
/*   Updated: 2021/05/10 18:31:05 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** Checks if token is one of the mandatory builtin function	
** @param:	- [char *] token to be checked
** @return:	[int] indicates if the token is a builtin or not
*/

int	is_builtin(t_list *tokens)
{
	int		check;
	char	*program_name;

	program_name = ((t_token *)tokens->data)->str;
	if (ft_strcmp(program_name, "echo") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "env") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "cd") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "pwd") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "export") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "unset") == 0)
		check = 1;
	else
		check = 0;
	return (check);
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
