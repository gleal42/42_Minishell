/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:47:16 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 11:25:22 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_MEMORY_H
# define FREE_MEMORY_H

# include "main.h"

void	free_msh(t_msh *msh);
void	free_ast(t_ast *ast);
void	free_cmd_table(void *cmd_table);
void	free_cmd(void *cmd);
void	free_redir(void *redir);

#endif
