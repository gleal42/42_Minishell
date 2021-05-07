/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:41:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/07 19:01:26 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "main.h"

t_ast		*get_ast(const char *input);
t_cmd_table	*get_cmd_table(const char *input, int *curr_pos);
t_cmd		*get_cmd(const char *input, int *curr_pos);
t_token		*get_token(const char *input, int *curr_pos);
t_redir		*get_redir(const char *input, int *curr_pos);

#endif
