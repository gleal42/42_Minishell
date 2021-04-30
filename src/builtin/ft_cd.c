/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:59:48 by gleal             #+#    #+#             */
/*   Updated: 2021/04/30 17:55:04 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_list *tokens, t_list **env)
{
	char	*arg;
	char	pwd_temp[1024];
	char	*pwd;

	if (getcwd(pwd_temp, 1024) == NULL)
		return (0);
	pwd = ft_strdup(pwd_temp);
	arg = ((t_token *)tokens->data)->str;
	if (arg == 0)
		change_dir_home(pwd, env);
	else if (arg[0] == '-' && arg[1] == '\0')
		change_to_old_dir(pwd, env);
	else if (chdir(arg) == 0)
		update_directories(pwd, env);
	free(pwd);
	return (0);
}

int	change_dir_home(char *cur_pwd, t_list **env)
{
	char	*home;

	home = ft_getenv("HOME");
	if (chdir(home) == 0)
		update_directories(cur_pwd, env);
	free(home);
	home = 0;
	return (0);
}

int	change_to_old_dir(char	*cur_pwd, t_list **env)
{
	char	*old_dir;

	old_dir = ft_getenv("OLDPWD");
	if (!old_dir)
	{
		printf("OLDPWD not set\n");
		return (1);
	}
	if (chdir(old_dir) == 0)
		update_directories(cur_pwd, env);
	free(old_dir);
	old_dir = 0;
	return (0);
}
