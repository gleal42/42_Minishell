/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 11:22:12 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections_pipes.h"

void	set_redirs_pipes(t_list *redirs,
							int nb_cmds,
							int **pipes,
							int process_index)
{
	int		fd;

	fd = 0;
	if (has_redirs(redirs, "input"))
	{
		fd = open_files(redirs, "input");
		if (fd == 0)
			return ;
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (process_index != 0)
		dup2(pipes[process_index - 1][0], STDIN_FILENO);
	fd = 0;
	if (has_redirs(redirs, "output"))
	{
		fd = open_files(redirs, "output");
		if (fd == 0)
			return ;
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (process_index != nb_cmds - 1)
		dup2(pipes[process_index][1], STDOUT_FILENO);
	g_msh.exit_status = EXIT_SUCCESS;
}

int	has_redirs(t_list *redirs, char *type)
{
	int		check;
	t_redir	*redir;

	check = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->data;
		if (!ft_strcmp(type, "input") && !ft_strcmp(redir->type, "<"))
		{
			check = 1;
			break ;
		}
		if (!ft_strcmp(type, "output")
			&& (!ft_strcmp(redir->type, ">") || !ft_strcmp(redir->type, ">>")))
		{
			check = 1;
			break ;
		}
		redirs = redirs->next;
	}
	return (check);
}

int	open_files(t_list *redirs, char *type)
{
	t_redir	*redir;
	int		fd;

	fd = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->data;
		if (!ft_strcmp(type, "input") && !ft_strcmp(redir->type, "<"))
			fd = open_file_input(redir, fd);
		if (!ft_strcmp(type, "output")
			&& (!ft_strcmp(redir->type, ">") || !ft_strcmp(redir->type, ">>")))
			fd = open_file_output(redir, fd);
		if (fd == 0)
			return (fd);
		redirs = redirs->next;
	}
	return (fd);
}

int	open_file_input(t_redir *redir, int fd)
{
	char	*file_name;

	file_name = redir->direction->str;
	if (fd != 0)
		close(fd);
	if (!ft_strcmp(redir->type, "<"))
		fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		write_gen_func_err_message(file_name, strerror(errno));
		g_msh.exit_status = errno;
		return (0);
	}
	return (fd);
}

int	open_file_output(t_redir *redir, int fd)
{
	char	*file_name;

	file_name = redir->direction->str;
	if (fd != 0)
		close(fd);
	if (!ft_strcmp(redir->type, ">"))
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (!ft_strcmp(redir->type, ">>"))
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		write_gen_func_err_message(file_name, strerror(errno));
		g_msh.exit_status = errno;
		return (0);
	}
	return (fd);
}
