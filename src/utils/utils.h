/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:39 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/07 22:35:42 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "main.h"

void	write_prompt(void);
void	write_gen_err_message(char *err_message);
void	write_func_err_message(char *func_name, char *err_message);
void	write_gen_func_err_message(char *func_name, char *err_message);
char	**convert_list_to_arr(t_list *lst);
char	**convert_list_to_arr_tokens(t_list *lst);

#endif
