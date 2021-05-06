/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/06 13:02:41 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"

/*
** File execute.c
*/

void	execute_ast(t_ast **ast, t_list **env);
void	execute_cmd_table(t_cmd_table *cmd_table, t_list **env);
void	execute_cmd(t_cmd *cmd);
// void	execute_cmd(t_cmd *cmd, t_list **env, int pipe);

/*
** File execute_utils.c
*/

int		is_builtin(char *first_token);
int		execute_builtin(t_list	*tokens, t_list **env);
int		*init_pids(int nb_cmds);
int		**init_pipes(int nb_cmds);

#endif
