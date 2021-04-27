/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:39 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/27 18:43:21 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "main.h"

void	write_prompt(void);
void	write_gen_err_message(char *err_message);
void	init_minishell(t_msh *msh);
void	ft_exit(t_msh *msh, int exit_code);
void	free_msh(t_msh *msh);

#endif
