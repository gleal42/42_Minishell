/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_pipes.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:57 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 11:16:40 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_PIPES_H
# define REDIRECTIONS_PIPES_H

# include "main.h"

void	set_redirs_pipes(t_list *redirs,
			int nb_cmds,
			int **pipes,
			int process_index);
int		has_redirs(t_list *redirs, char *type);
int		open_files(t_list *redirs, char *type);
int		open_file_input(t_redir *redir, int fd);
int		open_file_output(t_redir *redir, int fd);

#endif
