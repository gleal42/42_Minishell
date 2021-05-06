/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/06 20:26:00 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"

/*
** File execute.c
*/

void	execute_ast(t_ast **ast);
void	execute_cmd_table(t_cmd_table *cmd_table);
void	exec_child_process(t_cmd *cmd,
							int **pipes,
							int nb_cmds,
							int process_index);
void	execute_cmd(t_cmd *cmd);
void	exec_parent_process(int nb_cmds);

/*
** File execute_utils.c
*/

int		is_builtin(char *first_token);
int		execute_builtin(t_list	*tokens, t_list **env);
pid_t	*init_pids(int nb_cmds);
int		**init_pipes(int nb_cmds);

#endif
