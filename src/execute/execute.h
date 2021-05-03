/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/03 23:36:39 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"
# include "environment.h"
# include "builtins.h"

/*
** File execute.c
*/

int		execute_ast(t_ast **ast, t_list **env);
int		execute_cmd_table(t_cmd_table *cmd_table,
			t_list **env, int	last_status);
int		execute_cmd(t_cmd *cmd, t_list **env, int pipe, int last_status);

/*
** File execute_program.c
*/

int		execute_program(char **tokens, t_list *redirs, char **envp);
int		has_path(char *first_token);
char 	*get_abs_path(char *program_name);
void	add_slash(char ***path_envs);

/*
** File execute_utils.c
*/

int		is_builtin(char *first_token);
int		execute_builtin(t_list	*tokens, t_list **env);

#endif
