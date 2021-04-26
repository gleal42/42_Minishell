/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:37:34 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/26 16:05:26 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HISTORY_H
# define CMD_HISTORY_H

#include "main.h"

void	set_termcaps(t_dlist **cmd_history);
void	init_termcaps(t_dlist **cmd_history, char **buffer);
void	output_cmd(const char *raw_input);
void	turn_off_canonical_processing(void);

#endif
