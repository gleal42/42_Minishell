/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:41:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 11:00:08 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "main.h"
# include "parse_utils.h"
# include "input_validation.h"

/*
** File parse1.c
*/

char		*get_raw_input(void);
t_cmd_table	*get_cmd_table(const char *raw_input, int *curr_pos);
t_cmd		*get_cmd(const char *raw_input, int *curr_pos);
t_token		*get_token(const char *raw_input, int *curr_pos);

/*
** File parse2.c
*/

t_list		*get_redirs(const char *raw_input, int *curr_pos);
t_redir		*get_single_redir(const char *raw_input, int *curr_pos);

#endif
