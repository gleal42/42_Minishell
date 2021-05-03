/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:47:16 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/01 17:05:37 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_MEMORY_H
# define FREE_MEMORY_H

# include "main.h"

/*
** File free_memory1.c
*/

void	free_msh(t_msh *msh);

/*
** File free_memory2.c
*/

void	free_ast(t_ast *ast);
void	free_cmd_table(void *cmd_table);
void	free_cmd(void *cmd);
void	free_redir(void *redir);
void	free_token(void *token);

#endif
