/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/14 11:20:41 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections_pipes.h"

/*
** Creates a 2D array of ints where each subarray will represent a pipe, meaning
** it will have 2 ints:
** - [0] reading end of the pipe
** - [1] writing end of the pipe
** @param:	- [int] number of simple commands to be executed
** @return:	[int **] 2D array of ints. It's NULL-terminated to call free_arr()
** Line-by-line comments:
** @6		We effectively need (nb_cmds - 1) pipes but we also need the array
**			to be NULL-terminated
** @15		The function pipe() requires an array of 2 pre-allocated ints. It
**			enables reading and writing from different processes
*/

int	**init_pipes(int nb_cmds)
{
	int	**pipes;
	int	i;

	if (nb_cmds == 1)
		return (0);
	pipes = ft_calloc(nb_cmds, sizeof(int *));
	if (!pipes)
		quit_program(EXIT_FAILURE);
	i = 0;
	while (i < nb_cmds - 1)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i])
			quit_program(EXIT_FAILURE);
		if (pipe(pipes[i]) == -1)
			quit_program(EXIT_FAILURE);
		i++;
	}
	return (pipes);
}

/*
** Adjusts the input / output streams to implement piping and redirections. One
** thing we need to keep in mind: redirections (e.g. >, <) have priority over
** pipes!
** @param:	- [t_list *] linked list with redirections (t_redir *) as nodes
**			- [int] nb of simple command that are in the cmd_table. Info needed
**					for piping (choosing where to read/write and closing them)
**			- [int **] 2D array of ints. Each subarray is a pipe
**			- [int] index of the current process
** @return:	[type] return_value
** Line-by-line comments:
** @4&15	Order of if / else if important because priority of the redirections
** @6		We'll receive the file descriptor of the file where the program
**			will read from. In case, there are more than one input redirection,
**			in open_all_files(), we'll just close the first ones and keep the last
**			one
** @7-8		If there was an issue (e.g. file invalid, couldn't open file), 
**			the exit status has been set to errno and we receive -1
** @9-10	Set input stream directed from fd instead of STDIN and close the fd.
**			Closing it doesn't mean that it isn't active
** @12		If we don't have input redirections, then it means that its input
**			comes from the previous simple command. Unless it's the first one.
** @13		We read from the pipe (process_index - 1)[0] because the previous
**			index write to that same pipe but to its writing end [1]
** @15-24	Exact same logic
** @23		If no input redirections, then write to the next process. Unless
**			it's the last simple command
** @24		We write to [1] so that the next simple command can read from [0]
*/

void	set_redirs_pipes(t_list *redirs,
							int nb_cmds,
							int **pipes,
							int process_index)
{
	int		fd;

	if (has_redirs(redirs, "<"))
	{
		fd = open_all_files(redirs, "input");
		if (fd == -1)
			return ;
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (process_index != 0)
		dup2(pipes[process_index - 1][0], STDIN_FILENO);
	if (has_redirs(redirs, ">") || has_redirs(redirs, ">>"))
	{
		fd = open_all_files(redirs, "output");
		if (fd == -1)
			return ;
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (process_index != nb_cmds - 1)
		dup2(pipes[process_index][1], STDOUT_FILENO);
	g_msh.exit_status = EXIT_SUCCESS;
}

/*
** Checks if the redirs linked list has redirections of the specified type
** @param:	- [t_list *] linked list with redirs (t_redir *) as nodes
**			- [char *] type of redirection we are looking for. Can be
**					   either ">", ">>" or "<"
** @return:	[int] true or false
*/

int	has_redirs(t_list *redirs, char *type)
{
	int		check;
	t_redir	*redir;

	check = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->data;
		if (!ft_strcmp(redir->type, type))
		{
			check = 1;
			break ;
		}
		redirs = redirs->next;
	}
	return (check);
}

/*
** Opens all files relating the specified type. Only the last of its type is
** left open. For input type, we create them and leave them empty
** @param:	- [t_list *] linked list with redirs (t_redir *) as nodes
**			- [char *] type of stream, either "input" or "output"
** @return:	[int] the file descriptor of the file left opened
** Line-by-line comments:
** @14-15	If any of the open_file() calls returned -1, it means there was an
**			error
*/

int	open_all_files(t_list *redirs, char *type)
{
	int		fd;
	t_redir	*redir;

	fd = -2;
	while (redirs)
	{
		redir = (t_redir *)redirs->data;
		if (!ft_strcmp(type, "input") && !ft_strcmp(redir->type, "<"))
			fd = open_file(redir, fd, O_RDONLY, 0);
		else if (!ft_strcmp(type, "output") && !ft_strcmp(redir->type, ">"))
			fd = open_file(redir, fd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (!ft_strcmp(type, "output") && !ft_strcmp(redir->type, ">>"))
			fd = open_file(redir, fd, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			return (-1);
		redirs = redirs->next;
	}
	return (fd);
}

/*
** Opens a single file based on the flags and permissions passed
** @param:	- [t_list *] linked list with redirs (t_redir *) as nodes
**			- [int] previous file descriptor. If -2 then no file has been opened
**                  otherwise it means, another file is about to be opened and
**                  we need to close the previous one
**			- [int] flags in a bit field format
**			- [mode_t] permissions in a bit field format
** @return:	[int] file descriptor of the new file opened
** Line-by-line comments:
** @4-5		If -2 then no file has been opened previously. Otherwise it means,
**			another file is about to be opened and we need to close the
**			previous one
*/

int	open_file(t_redir *redir, int prev_fd, int flags, mode_t permissions)
{
	char	*file_name;
	int		new_fd;

	if (prev_fd != -2)
		close(prev_fd);
	file_name = redir->direction->str;
	new_fd = open(file_name, flags, permissions);
	if (new_fd == -1)
	{
		write_gen_func_err_message(file_name, strerror(errno));
		g_msh.exit_status = errno;
	}
	// else
	// {
	// 	if (!ft_strcmp(redir->type, "<"))
	// 		dup2(new_fd, STDIN_FILENO);
	// 	else if (!ft_strcmp(redir->type, ">") || !ft_strcmp(redir->type, ">"))
	// 		dup2(new_fd, STDOUT_FILENO);
	// 	close(new_fd);
	// }
	return (new_fd);
}
