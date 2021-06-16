/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:06:35 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/15 20:27:24 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

# include "main.h"

/*
** File input_validation1.c
*/

int	is_input_valid(const char *input);
int	is_input_valid_unexpected_token(const char *input, char *err_message);
int	is_input_valid_not_supported(const char *input, char *err_message);
int	has_quotes_open(const char *input, char *error_message);
int	has_char_at_beginning(const char *input, char c, char *error_message);

/*
** File input_validation2.c
*/

int	has_char_at_end(const char *input, char c, char *error_message);
int	has_forbidden_sequence(const char *input, char *test, char *error_message);
int	has_spaces_between_char(const char *input, char c, char *error_message);
int	has_non_supported(const char *input, char *test, char *error_message);
int	has_non_supported_one(const char *input, char *test, char *err_message);

#endif
