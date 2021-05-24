/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:59:16 by gleal             #+#    #+#             */
/*   Updated: 2021/05/24 17:51:29 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "main.h"

/*
** File environment1.c
*/

void	replace_envs(t_list **tokens, t_list *redirs);
void	replace_env_single_token(char **token);
void	replace_vars_with_values(char **str);
void	replace_tilde_with_home(char **token);
char	*get_last_exec_name(char *env_var);

/*
** File environment2.c
*/

char	*ft_getenv(char *key);
void	duplicate_env(t_list **dup_envp, char **envp);
void	remove_env_value(char	*key);
void	replace_status_env(char **str, int	last_status);
int		is_path_executable(char *exec_file);

/*
** File environment3.c
*/

t_list	*get_split_token(char *token);
char	*join_split_token(t_list *split_token);
int		get_new_token_size(t_list *split_token);
void	replace_one_var(char **str);

/*
** File save_last_token.c
*/

void	save_last_token(t_cmd_table *cmd_table);
char	*convert_to_path(char *token);

#endif