/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:20:04 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 10:20:33 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_UTILS_H
# define EXECUTE_UTILS_H

# include "main.h"

int		**init_pipes(int nb_cmds);
int		is_builtin(t_list *tokens);

#endif
