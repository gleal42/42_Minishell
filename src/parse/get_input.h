/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:28:18 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 11:36:15 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_INPUT_H
# define GET_INPUT_H

# include "main.h"

/*
** File get_input1.c
*/

char	*get_input(t_dlist *input_history, t_termcaps *termcaps);
int		is_up_down_arrow(char *buf, t_termcaps *termcaps);
void	parse_input_history(t_dlist **input_history,
			t_termcaps *termcaps,
			char *buf,
			int *i);
int		has_history(t_dlist *input_history, t_termcaps *termcaps, char *buf);
void	delete_single_char(t_termcaps *termcaps, char *buf, int *i);

/*
** File get_input2.c
*/

void	reset_cmd_line(char *buf, int *i, t_dlist **input_history);
void	exit_program(char *buf, int i);
char	*extract_input(char *buf, int i);

#endif
