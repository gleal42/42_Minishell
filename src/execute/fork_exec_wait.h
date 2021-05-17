/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec_wait.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:41:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/17 20:29:03 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_EXEC_WAIT_H
# define FORK_EXEC_WAIT_H

# include "main.h"

void	exec_child(char **tokens, char **envp, int nb_cmds, int **pipes);
void	exec_parent(void);
void	close_all_pipes(int **pipes, int nb_cmds);
pid_t	*init_pids(int nb_cmds);

#endif
