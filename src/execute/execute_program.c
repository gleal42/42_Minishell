/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 22:10:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/04 14:35:15dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** Executes a program. The program can either be local (e.g. ./a.out) or
** placed in a bin folder (e.g. ls or node)
** @param:	- [char **] param_value
**			- [type] param_value
** @return:	[type] return_value
** Line-by-line comments:
** @9		Fork returns twice more or less at the same time:
**			- a first time inside the child process with the value 0
**			- a second time inside the parent process with the value of the
**			process id of the child
** @14		The wait function allows to stop the parent process while the child
**			process is running
*/

void	execute_program(char **tokens, t_list *redirs, char **envp)
{
	pid_t	pid;
	int		status;
	char	*abs_path;

	if (has_path(tokens[0]))
		abs_path = ft_strdup(tokens[0]);
	else
		abs_path = get_absolute_path(tokens[0]);
	pid = fork();	
	if (pid == 0)
	{
		execve(abs_path, tokens, envp);
		if (errno == ENOENT)
		{
			write_func_err_message(tokens[0], "command not found");
			ft_exit(EXIT_CMD_NOT_FOUND);
		}
		else
			ft_exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		pid = wait(&status);
		if (WIFEXITED(status))
			g_msh.exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_msh.exit_status = WTERMSIG(status);
	}
	if (pid < 0)
		ft_exit(EXIT_FAILURE);
	free(abs_path);
	(void)redirs;
}

int	has_path(char *first_token)
{
	int	check;

	if (*first_token == '.' || *first_token == '/')
		check = 1;
	else
		check = 0;
	return (check);
}

char *get_absolute_path(char *program_name)
{
	char		*absolute_path;
	char		*path_env;
	char		**path_env_split;
	int			i;
	struct stat	statbuf;

	path_env = ft_getenv("PATH");
	if (!path_env)
	{
		absolute_path = ft_strdup(program_name);
		if (!absolute_path)
			ft_exit(EXIT_FAILURE);
		return (absolute_path);
	}
	path_env_split = ft_split(path_env, ":");
	free(path_env);
	if (!path_env_split)
		ft_exit(EXIT_FAILURE);
	add_slash(&path_env_split);
	i = 0;
	while (path_env_split[i])
	{
		absolute_path = ft_strjoin(path_env_split[i], program_name);
		if (!absolute_path)
			ft_exit(EXIT_FAILURE);
		if (stat(absolute_path, &statbuf) == EXIT_SUCCESS)
			break ;
		free(absolute_path);
		i++;
	}
	if (!path_env_split[i])
		absolute_path = ft_strdup(program_name);
	free_arr((void **)path_env_split);
	return (absolute_path);
}

void	add_slash(char ***path_env_split)
{
	int		i;
	char	*tmp;
	int		len;
	char	*path;

	i = 0;
	while ((*path_env_split)[i])
	{
		path = (*path_env_split)[i];
		len = ft_strlen(path);
		if (path[len - 1] != '/')
		{
			tmp = ft_strjoin(path, "/");
			free(path);
			(*path_env_split)[i] = tmp;
		}
		i++;
	}
}

// int	execute_program(char **tokens, t_list *redirs, char **envp)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();	
// 	if (pid == 0)
// 	{
// 		printf("\033[0;34m📌 Here in %s line %d\n\033[0m", __FILE__, __LINE__);
// 		execve(tokens[0], tokens, envp);
// 	}
// 	if (pid > 0)
// 	{
// 		printf("\033[0;34m📌 Here in %s line %d\n\033[0m", __FILE__, __LINE__);
// 		pid = wait(&status);
// 		if (WIFEXITED(status))
// 			printf("The process ended with exit(%d).\n", WEXITSTATUS(status));
// 		 if (WIFSIGNALED(status))
// 			printf("The process ended with kill -%d.\n", WTERMSIG(status));
// 	}
// 	if (pid < 0)
// 		perror("In fork():");
// 	// free_arr((void **)tokens);
// 	// free_arr((void **)envp);
// 	return (0);
// 	(void)redirs;
// }
