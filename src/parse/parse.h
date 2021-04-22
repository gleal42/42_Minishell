/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:41:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/22 20:28:31 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "main.h"

char	*get_raw_input(void);
int		has_quotes_open(const char *raw_input);
t_cmd	*get_cmd(const char *raw_input, int *curr_pos);
char	*get_token(const char *raw_input, int *curr_pos);

#endif
