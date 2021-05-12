/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:20:04 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 12:13:21 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_UTILS_H
# define EXECUTE_UTILS_H

# include "main.h"

int		**init_pipes(int nb_cmds);
int		is_builtin(t_list *tokens);
char	**convert_list_to_arr_envp(t_list *lst);
char	**convert_list_to_arr_tokens(t_list *lst);

#endif
