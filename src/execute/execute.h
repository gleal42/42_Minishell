/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/05 21:18:51 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"

/*
** File execute.c
*/

void	execute_ast(t_ast **ast, t_list **env);
void	execute_cmd_table(t_cmd_table *cmd_table, t_list **env);
void	execute_cmd(t_cmd *cmd, t_list **env, int pipe);

/*
** File execute_program.c
*/

void	execute_program(char **tokens, t_list *redirs, char **envp);
int		has_relative_path(char *first_token);
char	*get_absolute_path(char *program_name);
void	add_slash(char ***path_envs);

/*
** File execute_utils.c
*/

int		is_builtin(char *first_token);
int		execute_builtin(t_list	*tokens, t_list **env);

#endif
