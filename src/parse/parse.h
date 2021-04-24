/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:41:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 10:38:37 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "main.h"
# include "parse_utils.h"

int			is_input_valid(const char *raw_input);
t_cmd_table	*get_cmd_table(const char *raw_input, int *curr_pos);
t_cmd		*get_cmd(const char *raw_input, int *curr_pos);
char		*get_token(const char *raw_input, int *curr_pos);

#endif
