/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:37:34 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/26 18:06:35 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HISTORY_H
# define CMD_HISTORY_H

# include "main.h"
# include "cmd_history_utils.h"

void	set_termcaps(t_dlist *cmd_history);
void	init_termcaps(t_termcaps *termcaps);
void	turn_off_canonical_processing(void);
void	parse_cmd_history(t_dlist *cmd_history, t_termcaps *termcaps);

#endif
