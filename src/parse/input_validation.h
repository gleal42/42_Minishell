/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:06:35 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 14:10:20 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

# include "main.h"

int	is_input_valid(const char *raw_input);
int	has_quotes_open(const char *raw_input);
int	has_pipe_at_end(const char *raw_input);

#endif
