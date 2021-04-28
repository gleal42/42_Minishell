/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:27:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 12:25:05 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "main.h"

void	skip_spaces(const char *raw_input, int *curr_pos);
int		is_delimiter(char c);
char	get_delimiter(const char *raw_input, int *curr_pos);

#endif
