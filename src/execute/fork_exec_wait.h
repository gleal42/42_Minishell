/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec_wait.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:41:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 09:49:04 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_EXEC_WAIT_H
# define FORK_EXEC_WAIT_H

# include "main.h"

void	exec_child(char **tokens, char **envp, int nb_cmds, int **pipes);
void	exec_parent(int **pipes, int nb_cmds);
void	close_all_pipes(int **pipes, int nb_cmds);

#endif