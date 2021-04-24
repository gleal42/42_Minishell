/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:27:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 17:46:37 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "main.h"

char	*get_raw_input(void);
void	skip_spaces(const char *raw_input, int *curr_pos);
char	**convert_list_to_arr(t_list **lst);

/*
** Functions below will be deleted when project is finished
*/

void	print_cmd_table(t_cmd_table *cmd_table);
void	print_cmd(t_cmd *cmd);

#endif
