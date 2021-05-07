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
	(void)redirs;
	return (1);
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
	(void)redirs;
	return (1);
}
