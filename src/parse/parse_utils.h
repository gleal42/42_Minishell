/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:27:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 21:06:00 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "main.h"

void	skip_spaces(const char *raw_input, int *curr_pos);
char	**convert_list_to_arr(t_list **lst);
int		is_delimiter(char c);
int		is_executable(char *str);
void	set_quotes(const char *raw_input,
			int *curr_pos,
			int *has_dquotes_open,
			int *has_squotes_open);

/*
** Functions below will be deleted when project is finished
*/

void	print_cmd_table(t_cmd_table *cmd_table);
void	print_cmd(t_cmd *cmd);
void	print_redir(t_redir *redir);

#endif
