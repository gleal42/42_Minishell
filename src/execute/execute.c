/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:40:32 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/15 19:02:25 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** Executes all the command tables extracted by get_ast() from the user input
** @param:	- [t_ast *] struct with a list of cmd_table (t_cmd_table *) as nodes
** Line-by-line comments:
** @6		Each time a child process is created this var is incremented. It
**			allows to properly wait on all processes to finish before moving on
**			but still implementing asynchronous processes
** @7		Edge case: if the "exit" program name is used alongside others
**			simple commands we don't have to execute it. If it's the only simple
**			simple command, we do.
**			The way we implemented the execution, the exec_cmd() only has access
**			to the simple command it's executing. So we set a pointer to the
**			current cmd_table in our global variable struct
*/

void	exec_ast(t_ast *ast)
{
	t_list	*cmd_table;
	char	*delimiter;

	cmd_table = ast->cmd_tables;
	while (cmd_table)
	{
		g_msh.nb_forks = 0;
		g_msh.curr_cmd_table = cmd_table->data;
		exec_cmd_table(g_msh.curr_cmd_table);
		save_last_token(g_msh.curr_cmd_table);
		delimiter = g_msh.curr_cmd_table->delimiter;
		if (!ft_strcmp(delimiter, "&&") && g_msh.exit_status != EXIT_SUCCESS)
			break ;
		if (!ft_strcmp(delimiter, "||") && g_msh.exit_status == EXIT_SUCCESS)
			break ;
		cmd_table = cmd_table->next;
	}
}

/*
** Executes all the simple commands inside a command table. It does it
** consecutively and redirecting the input and output of the commands depending
** on the redirections and pipes. Redirections have priority over pipes.
** @param:	- [t_cmd_table *] current command table being executed. Struct with
**							  a linked list of simple commands (t_cmd *) and 
**							  a delimiter (" ", """, or "\'")
** Line-by-line comments:
** @8		We need (nb_cmds - 1) pipes to make all simple commands communicate.
**			We allocate a 2D array where each subarray will have 2 ints:
**			- [0] reading end of the pipe
**			- [1] writing end of the pipe
** @15		Each child process closed all the pipes, now the parent needs to do	
**			it one last time
** @16		All simple commands are executed asynchronously, so we'll only be
** 			executing the parent process once we looped through the list.
**			The parent process basically:
**			- Reaps the children processes
**			- Sets the exit_status of the last simple command executed
*/

void	exec_cmd_table(t_cmd_table *cmd_table)
{
	t_list	*cmds;
	int		nb_cmds;
	int		**pipes;
	int		i;

	cmds = cmd_table->cmds;
	nb_cmds = ft_lstsize(cmds);
	pipes = init_pipes(nb_cmds);
	i = 0;
	while (i < nb_cmds)
	{
		exec_cmd(cmds->data, nb_cmds, pipes, i);
		cmds = cmds->next;
		i++;
	}
	close_all_pipes(pipes, nb_cmds);
	exec_parent();
	free_arr((void **)pipes);
}

/*
** Executes a simple command. We only create a child process in exec_program().
** Meaning that builtin functions are executed on the parent process because
** functions like cd or export, need to actually change the environment
** variables so we can't execute them in a child process
** @param:	- [t_cmd *] struct with 2 linked lists, one for tokens (t_token *)
**						as nodes and the other for redirs (t_redir *)
**			- [int] nb of simple command that are in the cmd_table. Info needed
**					for piping (choosing where to read/write and closing them)
**			- [int **] 2D array of ints. Each subarray is a pipe
**			- [int] index of the current process
** Line-by-line comments:
** @4		For both tokens and redirections, we need to replace environment
**			variables like $HOME by their value
** @5-6		In set_redirs_pipes, we'll be messing with output and input streams
**			so we need to save the default ones to reset them back in
**			lines 15-16
** @8		Three cases where we don't execute anything:
** 			- Something went wrong with redirections (like an invalid file) so
**			we set exit_status to EXIT_SUCCESS if everything went well
**			- In replace_envs(), we might have deleted all tokens if they
**			were all invalid names
**			- No tokens have been inserted, only redirections like "> a >> b".
**			This example means we have to create 2 empty files
*/

void	exec_cmd(t_cmd *cmd, int nb_cmds, int **pipes, int process_index)
{
	int	saved_stdin;
	int	saved_stdout;

	replace_envs(&cmd->tokens, cmd->redirs);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	set_redirs_pipes(cmd->redirs, nb_cmds, pipes, process_index);
	if (g_msh.exit_status == EXIT_SUCCESS && cmd->tokens != 0)
	{
		if (is_builtin(cmd->tokens))
			exec_builtin(cmd->tokens, &g_msh.dup_envp);
		else
			exec_program(cmd->tokens, nb_cmds, pipes);
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

/*
** Redirects to builtin functions
** @param:	- [t_list *] list with tokens (t_token *) as nodes. Represents a
**						 simple command
**			- [t_list **] pointer to environment variable linked list
** Line-by-line comments:
** @4-6		We exit only if there is only one simple command in the current
**			command table
** @9-10	We were only asked to deal with env with no arguments
*/

void	exec_builtin(t_list *tokens, t_list **env)
{
	char	*program_name;

	program_name = ((t_token *)tokens->data)->str;
	if (ft_strcmp(program_name, "exit") == 0
		&& ft_lstsize(g_msh.curr_cmd_table->cmds) == 1)
		g_msh.exit_status = ft_exit(tokens->next);
	else if (ft_strcmp(program_name, "echo") == 0)
		g_msh.exit_status = ft_echo(tokens->next);
	else if ((ft_strcmp(program_name, "env") == 0) && ft_lstsize(tokens) == 1)
		g_msh.exit_status = ft_env(*env);
	else if (ft_strcmp(program_name, "cd") == 0
		&& ft_lstsize(g_msh.curr_cmd_table->cmds) == 1)
		g_msh.exit_status = ft_cd(tokens->next, env);
	else if (ft_strcmp(program_name, "pwd") == 0)
		g_msh.exit_status = ft_pwd();
	else if (ft_strcmp(program_name, "export") == 0)
		g_msh.exit_status = ft_export(tokens->next, env);
	else if (ft_strcmp(program_name, "unset") == 0)
		g_msh.exit_status = ft_unset(tokens->next, env);
}

/*
** Executes the program inside a child process
** @param:	- [t_cmd *] struct with 2 linked lists, one for tokens (t_token *)
**						as nodes and the other for redirs (t_redir *)
**			- [int] nb of simple command that are in the cmd_table. Info needed
**					for piping (choosing where to read/write and closing them)
**			- [int **] 2D array of ints. Each subarray is a pipe
** Line-by-line comments:
** @5-6		execve() requires NULL terminated array of string
** @7		Increment nb_forks to keep track of how many child processes where
**			created so that we can wait() for everyone of them before displaying
**			prompt
** @8		Fork() returns twice, a 1st time inside child process with pid == 0
**			and a 2nd time inside parent process with pid = process ID of child
**			so a value above 0
** @13-14	Although they are array of strings, we only need to free the
**			pointers because the individuals strings are still being used
*/

void	exec_program(t_list *lst_tokens, int nb_cmds, int **pipes)
{
	char	**tokens;
	char	**envp;
	pid_t	pid;

	tokens = convert_list_to_arr_tokens(lst_tokens);
	envp = convert_list_to_arr_envp(g_msh.dup_envp);
	g_msh.nb_forks++;
	pid = fork();
	if (pid < 0)
		quit_program(EXIT_FAILURE);
	else if (pid == 0)
		exec_child(tokens, envp, nb_cmds, pipes);
	free(tokens);
	free(envp);
}
