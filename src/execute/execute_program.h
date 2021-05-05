/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:08:09 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/05 17:08:55 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_PROGRAM_H
# define EXECUTE_PROGRAM_H

# include "main.h"

void	execute_program(char **tokens, t_list *redirs, char **envp);

#endif
