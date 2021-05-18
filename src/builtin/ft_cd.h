/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:58:24 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/18 16:57:00 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CD_H
# define FT_CD_H

# include "main.h"

/*
** File ft_cd.c
*/

int	ft_cd(t_list *tokens, t_list **env);
int	execute_cd(t_list *tokens, t_list **env, char *pwd);
int	only_cd_errors(t_list *args);
int	change_dir_home(char *cur_pwd, t_list **env);
int	change_to_old_dir(char *cur_pwd, t_list **env);

/*
** File ft_cd_utils.c
*/

int	cd_env_error_check(char *env);
int	cd_path_error_check(char *path);
int	cd_error_messsage(char *builtin, char *error);
int	other_invalid_error(char *builtin, int error, char *arg);
int	has_x_permission(char *path);

#endif
