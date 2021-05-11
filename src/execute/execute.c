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

void	exec_ast(t_ast *ast)
{
	t_list		*cmd_table;

	cmd_table = ast->cmd_tables;
	g_msh.cmd_table_nbr = 0;
	while (cmd_table)
	{
		exec_cmd_table(((t_cmd_table *)cmd_table->data)->cmds);
		cmd_table = cmd_table->next;
		g_msh.cmd_table_nbr++;
		g_msh.nb_forks = 0;
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

void	exec_cmd_table(t_list *cmds)
{
	int		nb_cmds;
	int		**pipes;
	int		i;

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
	while (g_msh.nb_forks > 0)
	{
		wait(&g_msh.exit_status);
		if (WIFEXITED(g_msh.exit_status))
			g_msh.exit_status = WEXITSTATUS(g_msh.exit_status);
		else if (WIFSIGNALED(g_msh.exit_status))
			g_msh.exit_status = WTERMSIG(g_msh.exit_status);
		g_msh.nb_forks--;
	}
	free_arr((void **)pipes);
}

void	exec_cmd(t_cmd *cmd, int nb_cmds, int **pipes, int process_index)
{
	int	saved_stdout;
	int	saved_stdin;

	replace_env_tokens(&cmd->tokens);
	replace_env_redirs(&cmd->redirs);
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
	cur_table_nb = g_msh.cmd_table_nbr;
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

void	exec_program(t_list *lst_tokens,
					int nb_cmds,
					int **pipes)
{
	char	*exec_path;
	char	**tokens;
	char	**envp;
	pid_t	pid;

	tokens = convert_list_to_arr_tokens(lst_tokens);
	envp = convert_list_to_arr(g_msh.dup_envp);
	if (has_relative_path(tokens[0]))
		exec_path = ft_strdup(tokens[0]);
	else
		exec_path = get_absolute_path(tokens[0]);
	g_msh.nb_forks++;
	pid = fork();
	if (pid < 0)
		exit_prog(EXIT_FAILURE);
	else if (pid == 0)
	{
		close_all_pipes(pipes, nb_cmds);
		execve(exec_path, tokens, envp);
		if (errno == ENOENT && ft_strcmp(tokens[0], "exit") != 0)
			write_func_err_message(tokens[0], "command not found");
		if (errno == ENOENT)
			exit(EXIT_CMD_NOT_FOUND);
		else
			exit(EXIT_FAILURE);
	}
	free(exec_path);
	free(tokens);
	free(envp);
}
