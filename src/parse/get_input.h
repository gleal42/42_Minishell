/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:28:18 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/29 19:46:51 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_INPUT_H
# define GET_INPUT_H

# include "main.h"
# include "parse_utils.h"
# include "input_validation.h"

int		is_up_down_arrow(char *buf, t_termcaps *termcaps);
void	parse_input_history(t_dlist **input_history,
							t_termcaps *termcaps,
							char *buf,
							int *i);
int		has_history(t_dlist *input_history,
					t_termcaps *termcaps,
					char *buf,
					int *i);

#endif
