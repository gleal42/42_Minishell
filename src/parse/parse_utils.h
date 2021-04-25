/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dds <dda-silv@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:27:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 13:59:36 by dds              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "main.h"

void	skip_spaces(const char *raw_input, int *curr_pos);
char	**convert_list_to_arr(t_list **lst);
int		is_delimiter(char c);
void	set_quotes(const char *raw_input,
			int *curr_pos,
			int *has_dquotes_open,
			int *has_squotes_open);

#endif
