/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 10:20:42 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"

void	exec_ast(t_ast *ast);
void	exec_cmd_table(t_list *cmds);
void	exec_cmd(t_cmd *cmd, int nb_cmds, int **pipes, int process_index);
void	exec_builtin(t_list	*tokens, t_list **env);
void	exec_program(t_list *lst_tokens, int nb_cmds, int **pipes);

#endif
