/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:40:32 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 19:14:59 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** Executes all the command tables extracted by get_ast() from the user input
** @param:	- [t_ast *] struct with a list of cmd_table (t_cmd_table *) as nodes
** Line-by-line comments:
** @7		Each time a child process is created this var is incremented. It
**			allows to properly wait on all processes to finish before moving on
**			but still implementing asynchronous processes
** @10		Edge case: if the "exit" program name is used alongside others
**			simple commands we don't have to execute it. If it's the only simple
**			simple command, we do.
**			The way we implemented the execution, the exec_cmd() only has access
**			to the simple command it's executing. So we count the cmd_tables as
**			they are being executed so that we can check all simple commands
**			within the current cmd_table
*/

void	exec_ast(t_ast *ast)
{
	t_list		*cmd_table;

	cmd_table = ast->cmd_tables;
	g_msh.nb_cmd_tables = 0;
	while (cmd_table)
	{
		g_msh.nb_forks = 0;
		exec_cmd_table(cmd_table->data);
		cmd_table = cmd_table->next;
		g_msh.nb_cmd_tables++;
	}
}

/*
** Executes all the simple commands inside a command table. It does it
** consecutively and redirecting the input and output of the commands depending
** on the redirections and pipes. Redirections have priority over pipes.
** @param:	- [t_cmd_table *] current command table being executed. Struct with
**							  (series
** of interconnected commands)
** Line-by-line comments:
** @7-10	if there are sevaral commands in a command table
**			then they need to be connected somehow (otherwise they
**			would be categorized as a single command with 
**			multiple arguments)
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
	exec_parent(pipes, nb_cmds);
	free_arr((void **)pipes);
}

void	exec_cmd(t_cmd *cmd, int nb_cmds, int **pipes, int process_index)
{
	int	saved_stdout;
	int	saved_stdin;

	replace_envs(&cmd->tokens, cmd->redirs);
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	set_redirs_pipes(cmd->redirs, nb_cmds, pipes, process_index);
	if (g_msh.exit_status == EXIT_SUCCESS && cmd->tokens != 0)
	{
		if (is_builtin(cmd->tokens))
			exec_builtin(cmd->tokens, &g_msh.dup_envp);
		else
			exec_program(cmd->tokens, nb_cmds, pipes);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

/*
** Redirects to builtin functions
** @param:	- [t_list *] list of tokens in a command
**			- [t_list **] pointer to environment variable linked list
** @return:	[int] command return values
** Line-by-line comments:
** @6			we're only asked to deal with env with no arguments
*/

void	exec_builtin(t_list *tokens, t_list **env)
{
	char	*program_name;
	t_list	*cur_table;
	int		cur_table_nb;

	cur_table = g_msh.ast->cmd_tables;
	cur_table_nb = g_msh.nb_cmd_tables;
	program_name = ((t_token *)tokens->data)->str;
	while (cur_table_nb-- > 0)
		cur_table = cur_table->next;
	if (is_exit(((t_cmd_table *)cur_table->data)->cmds))
		ft_exit(((t_cmd_table *)cur_table->data)->cmds);
	else if (ft_strcmp(program_name, "echo") == 0)
		g_msh.exit_status = ft_echo(tokens->next);
	else if ((ft_strcmp(program_name, "env") == 0) && tokens->next == 0)
		g_msh.exit_status = ft_env(*env);
	else if (ft_strcmp(program_name, "cd") == 0)
		g_msh.exit_status = ft_cd(tokens->next, env);
	else if (ft_strcmp(program_name, "pwd") == 0)
		g_msh.exit_status = ft_pwd();
	else if (ft_strcmp(program_name, "export") == 0)
		g_msh.exit_status = ft_export(tokens->next, env);
	else if (ft_strcmp(program_name, "unset") == 0)
		g_msh.exit_status = ft_unset(tokens->next, env);
}

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
