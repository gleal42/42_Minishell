/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:44:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 21:35:11 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "main.h"

int		execute_cmd_table(t_cmd_table *cmd_table, t_list **env);
int		execute_cmd(t_cmd *cmd, t_list **env, int pipe);
void	ft_exit(int status);
int		is_builtin(char *first_token);
int		env_vars(char ***tokens, t_list **env);
int		replace_strstr_offset(char **cur_token, char *env, int start);
int		replace_var_with_value(char **tokens, char *var, t_list *env);
int		execute_builtin(char **tokens);
int		ft_echo(char **args);

#endif
