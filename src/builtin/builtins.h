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

/*
** File ft_echo.c
*/

int		has_repeated_char_in_str(char repeat_chr, char *str,
			unsigned int start);
/*
** File environment_utils.c
*/

int		is_env_var(char *potential_var, t_list *env);

/*
** File ft_cd.c
*/

int		change_dir_home(char	*cur_pwd, t_list **env);
int		change_to_old_dir(char	*cur_pwd, t_list **env);

/*
** File builtins_utils.c.c
*/

int		update_directories(char *old_dir, t_list **env);
int		update_environment_var(char *var, char *new_value, t_list *env);
char	*replace_env_value(char **env_ptr, char	*var_name, char *new_value);

#endif
