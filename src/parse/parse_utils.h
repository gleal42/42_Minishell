/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:27:15 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/05 10:21:04 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "main.h"

/*
** File parse_utils1.c
*/

int		is_delimiter(char c);
char	get_delimiter(const char *input, int *curr_pos);
char	*ft_strstr_quotes(char *str, char *to_find);
void	skip_quotes(char *str, int *i);
void	skip_spaces(const char *input, int *curr_pos);

/*
** File parse_utils2.c
*/

void	delete_backslashes(t_token *token);
void	delete_quotes(char *str);

#endif
