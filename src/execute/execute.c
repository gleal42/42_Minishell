/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 22:23:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/09 18:26:50gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** This function executes all the command tables entered by the user.
** At the moment it simply executes each command independently of the
** exit status of the other command tables.
** @param:	- [t_ast *] struct that contains all the command and typed
**						information;
**			- [t_list **] Pointer to linked list with all the
**							environment variables;
** @return:	[int] exit status of the function;
** Line-by-line comments:
** @1-3		Inside the ast struct there are linked lists in which
**			t_list->data corresponds to a t_cmd_table struct, which 
**			contains all the command table information (commands, delimiters
**			and return value).
*/

void	execute_ast(t_ast *ast)
{
	t_list		*cmd_table;

	cmd_table = ast->cmd_tables;
	while (cmd_table)
	{
		if (is_exit(((t_cmd_table *)cmd_table->data)->cmds))
			ft_exit(((t_cmd_table *)cmd_table->data)->cmds);
		else
			execute_cmd_table(((t_cmd_table *)cmd_table->data)->cmds);
		cmd_table = cmd_table->next;
	}
}

/*
** Redirections still need to be implemented. For each command table
** this function will execute each command consecutively and redirect
** the input and output to the following commands if the redirection
** signs are present. (ask why pipes are not redirections).
** @param:	- [t_cmd_table] Current command table being executed(series
** of interconnected commands)
**			- [t_list **] Pointer to linked list with all the
**							environment variables;
** @return:	[int] exit status of the command table;
** Line-by-line comments:
** @7-10	if there are sevaral commands in a command table
**			then they need to be connected somehow (otherwise they
**			would be categorized as a single command with 
**			multiple arguments)
*/

void	execute_cmd_table(t_list *cmds)
{
	int		nb_cmds;
	pid_t	*pids;
	int		**pipes;
	int		i;

	nb_cmds = ft_lstsize(cmds);
	pids = init_pids(nb_cmds);
	pipes = init_pipes(nb_cmds);
	i = 0;
	while (i < nb_cmds)
	{
		if (cmds->next == 0)
			check_exit(cmds->data);
		pids[i] = fork();
		if (pids[i] < 0)
			exit_prog(EXIT_FAILURE);
		else if (pids[i] == 0)
			exec_child_process(cmds->data, pipes, nb_cmds, i);
		else if (pids[i] > 0)
			exec_parent_process(nb_cmds, pids[i], pipes, i);
		cmds = cmds->next;
		i++;
	}
	free(pids);
	free_arr((void **)pipes);
}

void	exec_child_process(t_cmd *cmd,
							int **pipes,
							int nb_cmds,
							int process_index)
{
	int		fd_input;
	int		fd_output;
	
	if (g_msh.exit_status == 3 && process_index != 0)
	{
		if (process_index == nb_cmds - 1)
			printf("Quit: 3\n");
		signal(SIGQUIT, SIG_DFL);
		kill(0, SIGQUIT);
	}
	if (has_redirs_input(cmd->redirs))
	{
		fd_input = set_redirs_input(cmd->redirs);
		dup2(fd_input, STDIN_FILENO);
		close(fd_input);
	}
	else if (process_index != 0)
		dup2(pipes[process_index - 1][0], STDIN_FILENO);
	if (has_redirs_output(cmd->redirs))
	{
		fd_output = set_redirs_output(cmd->redirs);
		dup2(fd_output, STDOUT_FILENO);
		close(fd_output);
	}
	else if (process_index != nb_cmds - 1)
		dup2(pipes[process_index][1], STDOUT_FILENO);
	close_all_pipes(pipes, nb_cmds);
	execute_cmd(cmd);
}

void	execute_cmd(t_cmd *cmd)
{
	char	**tokens;
	char	**envp;

	tokens = convert_list_to_arr_tokens(cmd->tokens);
	envp = convert_list_to_arr(g_msh.dup_envp);
	env_vars(cmd->tokens);
	if (is_builtin(tokens[0]))
		execute_builtin(cmd->tokens, &g_msh.dup_envp);
	else
	{
		execute_program(tokens, envp, cmd->redirs);
		if (errno == ENOENT && ft_strcmp(tokens[0], "exit") != 0)
			write_func_err_message(tokens[0], "command not found");
	}
	free(tokens);
	free(envp);
	if (errno == ENOENT)
		exit(EXIT_CMD_NOT_FOUND);
	else
		exit(EXIT_FAILURE);
}

void	exec_parent_process(int nb_cmds,
							pid_t pid,
							int **pipes,
							int process_index)
{
	int	status;

	if (nb_cmds == process_index + 1)
		close_all_pipes(pipes, nb_cmds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_msh.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_msh.exit_status = WTERMSIG(status);
}
