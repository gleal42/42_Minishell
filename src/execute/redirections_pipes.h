/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_pipes.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:57 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/13 23:13:54 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_PIPES_H
# define REDIRECTIONS_PIPES_H

# include "main.h"

int		**init_pipes(int nb_cmds);
void	set_redirs_pipes(t_list *redirs,
			int nb_cmds,
			int **pipes,
			int process_index);
int		has_redirs(t_list *redirs, char *type);
int		open_all_files(t_list *redirs, char *type);
int		open_file(t_redir *redir, int prev_fd, int flags, mode_t permissions);

#endif
