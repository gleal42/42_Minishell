/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:42:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/06 16:11:44dda-silv         ###   ########.fr       */
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

void	execute_ast(t_ast **ast)
{
	t_list		*cmd_table;

	cmd_table = (*ast)->cmd_tables;
	while (cmd_table)
	{
		execute_cmd_table((t_cmd_table *)cmd_table->data);
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

void	execute_cmd_table(t_cmd_table *cmd_table)
{
	int	nb_cmds;
	pid_t	*pids;
	int	**pipes;
	int	i;
	t_list	*cmds;

	nb_cmds = ft_lstsize(cmd_table->cmds);
	pids = init_pids(nb_cmds);
	pipes = init_pipes(nb_cmds);
	i = 0;
	cmds = cmd_table->cmds;
	while (i < nb_cmds)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			ft_exit(EXIT_FAILURE);
		else if (pids[i] == 0)
			exec_child_process(cmds->data, pipes, nb_cmds , i);
		else if (pids[i] > 0)
			exec_parent_process(pids[i]);
		i++;
		cmds = cmds->next;
	}
	close(pipes[0][0]);
	close(pipes[0][1]);
	// close(pipes[1][0]);
	// close(pipes[1][1]);
	// i--;
	// while (i--)
	// {
	// 	close(pipes[i][0]);
	// 	close(pipes[i][1]);
	// }
}

void	exec_child_process(t_cmd *cmd,
							int **pipes,
							int nb_cmds,
							int process_index)
{
	if (process_index == 1)
		dup2(pipes[0][0], STDIN_FILENO);
	if (process_index == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	// if (process_index != 0)
	// 	dup2(pipes[process_index][0], STDIN_FILENO);
	// if (process_index != nb_cmds - 1)
	// 	dup2(pipes[process_index + 1][1], STDOUT_FILENO);
	// if (process_index != 0)
	// 	close(pipes[process_index][0]);
	// if (process_index != nb_cmds - 1)
	// 	close(pipes[process_index + 1][1]);
	// nb_cmds--;
	// while (nb_cmds--)
	// {
	// 	close(pipes[nb_cmds][0]);
	// 	close(pipes[nb_cmds][1]);
	// }
	close(pipes[0][0]);
	close(pipes[0][1]);
	// close(pipes[0][0]);
	// close(pipes[1][1]);
	execute_cmd(cmd);
	(void)nb_cmds;
}

void	execute_cmd(t_cmd *cmd)
{
	char	**tokens;
	char	**envp;

	env_vars(cmd->tokens);
	tokens = convert_list_to_arr_tokens(cmd->tokens);
	envp = convert_list_to_arr(g_msh.dup_envp);
	execute_program(tokens, envp, cmd->redirs);
	free(tokens);
	free(envp);
}

void	exec_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_msh.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_msh.exit_status = WTERMSIG(status);
}

	// t_list	*cmds;
	// int		pipe;

	// cmds = cmd_table->cmds;
	// while (cmds)
	// {
	// 	if (cmds->next == NULL)
	// 		pipe = 0;
	// 	else
	// 		pipe = 1;
	// 	execute_cmd((t_cmd *)cmds->data, env, pipe);
	// 	cmds = cmds->next;
	// }
// }

/*
** Executes the command based on the first token/word
** @param:	- [t_cmd *] current command
**			- [t_list **] pointer to linked list with all the environment
						  variables
**			- [int] idenfifies if the output will be redirected or if we should
**					execute the command
** @return:	[int] exit status of command
** Line-by-line comments:
** @7		Replaces environment variables by their values
** @12		Executes recreated functions (echo, cd, pwd, export, unset, env, exit)
*/

// void	execute_cmd(t_cmd *cmd, t_list **env, int pipe)
// {
// 	t_list	*tokens;
// 	char	*first;
// 	char	**arr_tokens;
// 	char	**arr_env;

// 	tokens = cmd->tokens;
// 	if (tokens == 0)
// 		return ;
// 	env_vars(tokens);
// 	arr_tokens = convert_list_to_arr_tokens(tokens);
// 	arr_env = convert_list_to_arr(*env);
// 	first = ((t_token *)tokens->data)->str;
// 	if (ft_strcmp(first, "exit") == 0 && pipe == 0)
// 		ft_exit(0);
// 	if (is_builtin(first))
// 		g_msh.exit_status = execute_builtin(tokens, env);
// 	else
// 		execute_program(arr_tokens, cmd->redirs, arr_env);
// 	free(arr_tokens);
// 	free(arr_env);
// }
