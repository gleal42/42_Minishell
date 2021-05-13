/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:25:18 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/13 18:29:59 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork_exec_wait.h"

/*
** Function only executed inside child process. This process will be replaced by
** execve()
** @param:	- [char **] param_value
**			- [type] param_value
**			- [int **] 2D array of ints. Each subarray is a pipe
**			- [int] index of the current process
** @return:	[type] return_value
** Line-by-line comments:
** @3		We need to close all the pipes in the child process because:
**			- we already changed the stdout and stdin inside set_redirs_pipes()
**			- all pipes opened in parent process are also considered open in
**			child BUT closing them in child doesn't close them in parent
** @7		We need to add the PATH of the executable
**			If valid executable:
**			- "ls" -> "/bin/ls"
**			- "go" -> "/usr/local/go/bin/go"
**			If invalid executable, the program name is just duplicated
** @9		If execve call is successful, the following lines are never executed
**			because the child process will kill itself when finished
** @10-11	We have to write "command not found" unless it's exit because if
**			a exit command reached here, it means it wasn't a valid exit use
** @15		130 error code for specifically when command not found
*/

void	exec_child(char **tokens, char **envp, int nb_cmds, int **pipes)
{
	char	*exec_path;

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
	if (errno == ENOENT && ft_strcmp(tokens[0], "exit") != 0)
		write_func_err_message(tokens[0], "command not found");
	free(exec_path);
	free(tokens);
	free(envp);
	if (errno == ENOENT)
		exit(EXIT_CMD_NOT_FOUND);
	else
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

void	exec_parent(void)
{
	int	exit_info;

	exit_info = 0;
	while (g_msh.nb_forks > 0)
	{
		wait(&exit_info);
		g_msh.nb_forks--;
		if (WIFEXITED(exit_info))
			g_msh.exit_status = WEXITSTATUS(exit_info);
		else if (WIFSIGNALED(exit_info))
			g_msh.exit_status = WTERMSIG(exit_info);
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
