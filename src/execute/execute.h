/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/30 15:44:43 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"

int		execute_cmd_table(t_cmd_table *cmd_table, t_list **env);
int		execute_cmd(t_cmd *cmd, t_list **env, int pipe);
void	ft_exit(int status);
int		is_builtin(char *first_token);
int		env_vars(t_list	*tokens);
int		replace_strstr_offset(char **cur_token, char *env, int start);
int		replace_var_with_value(char **tokens, char *var, t_list *env);
int		execute_builtin(t_list	*tokens, t_list **env);
int		ft_echo(t_list *token_args);
int		ft_env(t_list *env);
int		ft_cd(t_list *tokens, t_list **env);

#endif
