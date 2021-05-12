/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_term.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:39 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 12:14:55 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITE_TERM_H
# define WRITE_TERM_H

# include "main.h"

void	write_prompt(void);
void	write_gen_err_message(char *err_message);
void	write_func_err_message(char *func_name, char *err_message);
void	write_gen_func_err_message(char *func_name, char *err_message);

#endif
