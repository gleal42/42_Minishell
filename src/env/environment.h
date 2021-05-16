/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:59:16 by gleal             #+#    #+#             */
/*   Updated: 2021/05/15 22:20:40 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "main.h"

/*
** File environment1.c
*/

void	replace_envs(t_list **tokens, t_list *redirs);
void	replace_env_single_token(t_token *token);
void	replace_vars_with_values(char **str);
void	replace_tilde_with_home(char **str);
char	*getlastexecname(char *env_var);

/*
** File environment2.c
*/

char	*ft_getenv(char *key);
void	duplicate_env(t_list **dup_envp, char **envp);
void	remove_env_value(char	*key);
void	replace_status_env(char **str, int	last_status);
int		is_path_executable(char *exec_file);

/*
** File save_last_token.c
*/

void	save_last_token(t_cmd_table *cmd_table);
char	*convert_to_path(char *token);

#endif