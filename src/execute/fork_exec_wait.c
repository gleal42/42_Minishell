/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:25:18 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 10:26:47 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork_exec_wait.h"

/*
** Function only executed inside child process. This process will be replaced by
** execve()
** @param:	- [char **] NULL-terminated array of strings with the tokens
**			- [char **] NULL-terminated array of string with the environment
**						variables
**			- [int] number of commands in current cmd_table
**			- [int **] 2D array of ints. Each subarray is a pipe
** Line-by-line comments:
** @4		We need to close all the pipes in the child process because:
**			- we already changed the stdout and stdin inside set_redirs_pipes()
**			- all pipes opened in parent process are also considered open in
**			child BUT closing them in child doesn't close them in parent
** @12		We need to add the PATH of the executable
**			If valid executable:
**			- "ls" -> "/bin/ls"
**			- "go" -> "/usr/local/go/bin/go"
**			If invalid executable, the program name is just duplicated
** @13		If execve call is successful, the following lines are never executed
**			because the child process will kill itself when finished
** @16-17	We have to write "command not found" unless it's exit because if
**			a exit command reached here, it means it wasn't a valid exit use
** @24		127 error code for specifically when command not found
*/

void	exec_child(char **tokens, char **envp, int nb_cmds, int **pipes)
{
	char	*exec_path;

	signal(SIGINT, SIG_DFL);
	close_all_pipes(pipes, nb_cmds);
	if (has_relative_path(tokens[0]) || has_absolute_path(tokens[0]))
	{
		exec_path = ft_strdup(tokens[0]);
		if (!exec_path)
			quit_program(EXIT_FAILURE);
	}
	else
		exec_path = get_absolute_path(tokens[0]);
	execve(exec_path, tokens, envp);
	if (errno == EACCES)
		write_msh_exec_error(tokens[0], "Permission denied");
	else if (errno == ENOENT && ft_strcmp(tokens[0], "exit") != 0)
		write_msh_exec_error(tokens[0], "command not found");
	free(exec_path);
	free(tokens);
	free(envp);
	if (errno == EACCES)
		exit(EXIT_CMD_INTERRUPTED);
	else if (errno == ENOENT)
		exit(EXIT_CMD_NOT_FOUND);
	exit(errno);
}

/*
** Waits for all the child processes to be finished and sets the exit status
** Line-by-line comments:
** @6		wait() sets the exit information related to the child process it
**			just reaped
** @8-11	The child process can have exited (not necessarily successfully)
**			or have been forced to finish by a signal (like ctrl-C). Depending
**			on which, the macros help us set the exit_status
*/

void	exec_parent(t_list **pids)
{
	long	pid;
	int		exit_info;

	exit_info = 0;
	while (*pids)
	{
		pid = (long)(*pids)->data;
		waitpid(pid, &exit_info, 0);
		if (WIFEXITED(exit_info))
			g_msh.exit_status = WEXITSTATUS(exit_info);
		else if (WIFSIGNALED(exit_info))
			g_msh.exit_status = WTERMSIG(exit_info);
		ft_lstdel_first(pids, ft_lstdel_int);
	}
}

/*
** Closes all the pipes that were initiated in init_pipes()
** @param:	- [int **] 2D array of ints. Each subarray is a pipe
**			- [int] nb of simple command that are in the cmd_table. Info needed
**					for piping (choosing where to read/write and closing them)
*/

void	close_all_pipes(int **pipes, int nb_cmds)
{
	int	i;
	int	nb_pipes;

	i = 0;
	nb_pipes = nb_cmds - 1;
	while (i < nb_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
