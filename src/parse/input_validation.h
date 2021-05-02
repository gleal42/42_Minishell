/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:06:35 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/02 20:33:05 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

# include "main.h"

/*
** File input_validation1.c
*/

int		is_input_valid(const char *input);
int		has_quotes_open(const char *input, char *error_message);
int		has_char_at_beginning(const char *input, char c, char *error_message);
int		has_char_at_end(const char *input, char c, char *error_message);
int		has_non_supported(const char *input, char *test, char *error_message);

/*
** File input_validation2.c
*/

int		has_str(const char *input, char *test, char *error_message);
int		has_spaces_between_char(const char *input, char c, char *error_message);
char	*ft_strstr_quotes(char *str, char *to_find);

#endif
