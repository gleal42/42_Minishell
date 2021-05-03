/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:55:37 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/30 11:14:39 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "main.h"

void	init_termcaps(t_termcaps *termcaps);
int		has_capabilities(t_termcaps *termcaps);
void	turn_off_canonical_mode(t_termcaps *termcaps);
void	turn_on_canonical_mode(t_termcaps *termcaps);
int		ft_putint(int c);

#endif
