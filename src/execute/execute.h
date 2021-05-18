/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/18 10:08:17 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"

void	exec_ast(t_ast *ast);
void	exec_cmd_table(t_cmd_table *cmd_table);
void	exec_cmd(t_cmd *cmd, t_cmd_table *cmd_table, int process_index);
void	exec_builtin(t_list *tokens,
			t_list **env,
			int nb_cmds,
			int process_index);
void	exec_program(t_list *lst_tokens, t_cmd_table *cmd_table);

#endif
