/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:41:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/01 17:28:52 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "main.h"

/*
** File parse1.c
*/

t_cmd_table	*get_cmd_table(const char *input, int *curr_pos);
t_cmd		*get_cmd(const char *input, int *curr_pos);
t_token		*get_token(const char *input, int *curr_pos);

/*
** File parse2.c
*/

t_list		*get_redirs(const char *input, int *curr_pos);
t_redir		*get_single_redir(const char *input, int *curr_pos);

#endif
