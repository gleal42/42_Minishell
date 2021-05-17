/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:34:21 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/16 18:42:03 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_AST_H
# define PRINT_AST_H

# include "main.h"

/*
** Functions below will be deleted when project is finished
*/

void	print_ast(t_ast *ast);
void	print_cmd_table(t_cmd_table *cmd_table);
void	print_cmd(t_cmd *cmd);
void	print_token(char *token, int i);
void	print_redir(t_redir *redir);

#endif
