/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:25:18 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 10:26:09 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork_exec_wait.h"

void	exec_child(char **tokens, char **envp, int nb_cmds, int **pipes)
{
	char	*exec_path;

	if (has_relative_path(tokens[0]))
		exec_path = ft_strdup(tokens[0]);
	else
		exec_path = get_absolute_path(tokens[0]);
	close_all_pipes(pipes, nb_cmds);
	execve(exec_path, tokens, envp);
	if (errno == ENOENT && ft_strcmp(tokens[0], "exit") != 0)
		write_func_err_message(tokens[0], "command not found");
	free(exec_path);
	free(tokens);
	free(envp);
	if (errno == ENOENT)
		exit_prog(EXIT_CMD_NOT_FOUND);
	else
		exit_prog(EXIT_FAILURE);
}

void	exec_parent(int **pipes, int nb_cmds)
{
	close_all_pipes(pipes, nb_cmds);
	while (g_msh.nb_forks > 0)
	{
		wait(&g_msh.exit_status);
		if (WIFEXITED(g_msh.exit_status))
			g_msh.exit_status = WEXITSTATUS(g_msh.exit_status);
		else if (WIFSIGNALED(g_msh.exit_status))
			g_msh.exit_status = WTERMSIG(g_msh.exit_status);
		g_msh.nb_forks--;
	}
}

void	close_all_pipes(int **pipes, int nb_cmds)
{
	int	nb_pipes;

	nb_pipes = nb_cmds - 1;
	while (nb_pipes--)
	{
		close(pipes[nb_pipes][0]);
		close(pipes[nb_pipes][1]);
	}
}
