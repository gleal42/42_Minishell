/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:27:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/18 16:15:35 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "main.h"

/*
** File parse_utils1.c
*/

char	*ft_strstr_quotes(char *str, char *to_find);
void	skip_quotes(const char *str, int *i);
void	skip_spaces(const char *input, int *curr_pos);
void	skip_letters(const char *input, int *curr_pos);
void	delete_quotes(char *str);

/*
** File parse_utils2.c
*/

int		is_cmd_table_delimiter(const char *str);
int		is_cmd_delimiter(char c);
int		is_token_delimiter(char c);
char	*get_cmd_table_delimiter(const char *input, int *curr_pos);
int		is_ctrl(char c);

#endif
