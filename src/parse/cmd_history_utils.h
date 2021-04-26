/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:39:39 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/26 18:33:09 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HISTORY_UTILS_H
# define CMD_HISTORY_UTILS_H

# include "main.h"

int		ft_putint(int c);
void	get_cursor_position(int *col, int *row, t_termcaps *termcaps);

#endif
