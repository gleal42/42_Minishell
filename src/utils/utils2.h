/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:31:28 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 10:58:24 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS2_H
# define UTILS2_H

#include "main.h"

void	init_minishell(t_msh *msh, char **envp);
void	ft_exit(int exit_code);
void	duplicate_env(t_msh *msh, char **envp);

#endif
