/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:08:09 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/07 09:34:23 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_PROGRAM_H
# define EXECUTE_PROGRAM_H

# include "main.h"

void	execute_program(char **tokens, char **envp, t_list *redirs);
void	close_all_pipes(int **pipes, int nb_cmds);

#endif
