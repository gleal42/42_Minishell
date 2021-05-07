/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:15:39 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/07 19:22:57 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_UTILS2_H
# define EXECUTE_UTILS2_H

# include "main.h"

void	execute_program(char **tokens, char **envp, t_list *redirs);
void	close_all_pipes(int **pipes, int nb_cmds);
int		has_redirs_input(t_list *redirs);
int		set_redirs_input(t_list *redirs);
int		has_redirs_output(t_list *redirs);
int		set_redirs_output(t_list *redirs);

#endif
