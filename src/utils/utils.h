/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:39 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/03 19:06:09 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "main.h"

void	write_prompt(void);
void	write_gen_err_message(char *err_message);
char	**convert_list_to_arr(t_list *lst);
char	**convert_list_to_arr_tokens(t_list *lst);

#endif
