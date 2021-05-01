/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:59:48 by gleal             #+#    #+#             */
/*   Updated: 2021/05/01 22:49:49 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** change directories, first it saves the 
current directory to update OLDPWD env var
then based on the arguments it wll change to
different places
** @param:	- [t_list *] tokens in current command (different arguments)
**			- [t_list **] environment variable linked list
** @return:	[int] exit status(still need to confirm)
** Line-by-line comments:
** @5			get current directory for OLDPWD	
** @10-14		change to home in case of no args
** @16-17		change to old_pwd in case of hyphen
** @18-19		change to any other absolute or relative path
*/

int	ft_cd(t_list *tokens, t_list **env)
{
	char	*arg;
	char	pwd_temp[1024];
	char	*pwd;

	if (getcwd(pwd_temp, 1024) == NULL)
		return (0);
	pwd = ft_strdup(pwd_temp);
	if (!pwd)
		ft_exit(EXIT_FAILURE);
	if (tokens == 0)
	{
		change_dir_home(pwd, env);
		return (0);
	}
	arg = ((t_token *)tokens->data)->str;
	if (arg[0] == '-' && arg[1] == '\0')
		change_to_old_dir(pwd, env);
	else if (chdir(arg) == 0)
		update_directories(pwd, env);
	free(pwd);
	return (0);
}

/*
** changes directory to home
** @param:	- [char *] directory before changing (for future OLDPWD)
**			- [t_list *] environment variable linked list pointer
** @return:	[int] exit status (to be implemented)
** Line-by-line comments:
** @9	function will update the environment variable linked list 
** with the new working directory values
*/

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

/*
** changes directory to the old directory
** @param:	- [char *] directory before changing (for future OLDPWD)
**			- [t_list *] environment variable linked list pointer
** @return:	[int] exit status (to be implemented)
** Line-by-line comments:
** @9	function will update the environment variable linked list 
** with the new working directory values
*/

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
