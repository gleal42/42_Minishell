/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:04:57 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/10 18:19:45 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_UTILS3_H
# define EXECUTE_UTILS3_H

# include "main.h"

void	set_redirs_pipes(t_list *redirs,
			int nb_cmds,
			int **pipes,
			int process_index);
int		has_redirs_input(t_list *redirs);
int		set_redirs_input(t_list *redirs);
int		has_redirs_output(t_list *redirs);
int		set_redirs_output(t_list *redirs);

#endif
