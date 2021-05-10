/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/10 16:11:36 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_utils3.h"

void	set_redirs_pipes(t_list *redirs,
							int nb_cmds,
							int **pipes,
							int process_index)
{
	int		fd_input;
	int		fd_output;

	if (has_redirs_input(redirs))
	{
		fd_input = set_redirs_input(redirs);
		dup2(fd_input, STDIN_FILENO);
		close(fd_input);
	}
	else if (process_index != 0)
		dup2(pipes[process_index - 1][0], STDIN_FILENO);
	if (has_redirs_output(redirs))
	{
		fd_output = set_redirs_output(redirs);
		dup2(fd_output, STDOUT_FILENO);
		close(fd_output);
	}
	else if (process_index != nb_cmds - 1)
		dup2(pipes[process_index][1], STDOUT_FILENO);
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