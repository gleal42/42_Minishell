/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/01 22:35:58 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"

/*
** File execute.c
*/

int		execute_ast(t_ast *ast, t_list **env);
int		execute_cmd_table(t_cmd_table *cmd_table, t_list **env);
int		execute_cmd(t_cmd *cmd, t_list **env, int pipe);

/*
** File execute_utils.c
*/

int		is_builtin(char *first_token);
int		execute_builtin(t_list	*tokens, t_list **env);

/*
** File execute_utils.c
*/

int		env_vars(t_list	*tokens);

/*
** File utils2.c
*/

void	ft_exit(int status);

/*
** directory builtins / separate c files
*/

int		ft_echo(t_list *token_args);
int		ft_env(t_list *env);
int		ft_cd(t_list *tokens, t_list **env);
#endif
