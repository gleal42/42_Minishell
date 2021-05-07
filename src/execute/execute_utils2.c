/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 22:22:51 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/07 22:40:56 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_utils2.h"

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
** @15		If execve returns, it necessarily mean that execve failed
** @14		The wait function allows to stop the parent process while the child
**			process is running
** @25		WIFEXISTED - program terminated on its own
** @27		WIFSIGNALED - program was killed by a signal
** @25		If fork fails, it returns a negative value
*/

void	execute_program(char **tokens, char **envp, t_list *redirs)
{
	char	*exec_path;

	if (has_relative_path(tokens[0]))
		exec_path = ft_strdup(tokens[0]);
	else
		exec_path = get_absolute_path(tokens[0]);
	execve(exec_path, tokens, envp);
	free(exec_path);
	(void)redirs;
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

int	has_redirs_input(t_list *redirs)
{
	int		check;
	t_redir	*redir;

	check = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->data;
		if (!ft_strcmp(redir->type, "<"))
		{
			check = 1;
			break ;
		}
		redirs = redirs->next;
	}
	return (check);
}

int	set_redirs_input(t_list *redirs)
{
	int		fd_input;
	t_redir	*redir;
	char	*file;

	fd_input = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->data;
		if (!ft_strcmp(redir->type, "<"))
		{
			file = redir->direction->str;
			if (fd_input != 0)
				close(fd_input);
			fd_input = open(file, O_RDONLY);
			if (fd_input == -1)
			{
				write_gen_func_err_message(file, strerror(errno));
				exit(errno);
			}
		}
		redirs = redirs->next;
	}
	return (fd_input);
}

int	has_redirs_output(t_list *redirs)
{
	int		check;
	t_redir	*redir;

	check = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->data;
		if (!ft_strcmp(redir->type, ">") || !ft_strcmp(redir->type, ">>"))
		{
			check = 1;
			break ;
		}
		redirs = redirs->next;
	}
	return (check);
}

int	set_redirs_output(t_list *redirs)
{
	int		fd_output;
	t_redir	*redir;
	char	*file;

	fd_output = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->data;
		if (!ft_strcmp(redir->type, ">") || !ft_strcmp(redir->type, ">>"))
		{
			file = redir->direction->str;
			if (fd_output != 0)
				close(fd_output);
			if (!ft_strcmp(redir->type, ">"))
				fd_output = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (!ft_strcmp(redir->type, ">>"))
				fd_output = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd_output == -1)
			{
				write_gen_func_err_message(file, strerror(errno));
				exit(errno);
			}
		}
		redirs = redirs->next;
	}
	return (fd_output);
}
