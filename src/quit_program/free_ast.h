/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:47:16 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/16 18:46:35 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_AST_H
# define FREE_AST_H

# include "main.h"

void	free_ast(t_ast *ast);
void	free_cmd_table(void *cmd_table);
void	free_cmd(void *cmd);
void	free_redir(void *redir);

#endif
