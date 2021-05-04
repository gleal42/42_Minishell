/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 20:17:08 by gleal             #+#    #+#             */
/*   Updated: 2021/04/30 15:22:03by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"
# include "environment.h"

/*
** File ft_echo.c
*/

int		ft_echo(t_list *tokens);
int		has_repeated_char_in_str(char repeat_chr, char *str,
			unsigned int start);

/*
** File ft_cd.c
*/

int		ft_cd(t_list *tokens, t_list **env);
int		change_dir_home(char	*cur_pwd, t_list **env);
int		change_to_old_dir(char	*cur_pwd, t_list **env);

/*
** File ft_env.c
*/

int		ft_env(t_list *env);

/*
** File ft_pwd.c
*/

int		ft_pwd(void);

/*
** File ft_export.c
*/

int		ft_export(t_list *tokens, t_list **env);
int		print_all_exported_vars(t_list *env);
void	create_environment_var(char **token_str, t_list **env);

/*
** File ft_unset.c
*/

int		ft_unset(t_list *tokens, t_list **env);
int	has_valid_identifier(char *token_str);
int	is_token_valid_unset(char *token_str,char *err_message);

/*
** File builtins_utils.c.c
*/

int		update_directories(char *old_dir, t_list **env);
int		update_environment_var(char *var, char *new_value, t_list *env);
char	*replace_env_value(char **env_ptr, char	*var_name, char *new_value);

#endif
