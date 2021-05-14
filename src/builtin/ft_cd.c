/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:30:51 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/14 11:04:04 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cd.h"

/*
** Change directories, first it saves the current directory to update OLDPWD
** env var then based on the arguments it wll change to different places
** @param:	- [t_list *] tokens in current command (different arguments)
**			- [t_list **] environment variable linked list
** @return:	[int] exit status (1 if unsuccessful)
** Line-by-line comments:
** @5		Get current directory for OLDPWD
** @10-11	Change to home in case of no args
** @15-16	Change to old_pwd in case of hyphen
** @17-18	Change to any other absolute or relative path
** @19-23	Error message in case of failure
*/

int	ft_cd(t_list *tokens, t_list **env)
{
	char	*arg;
	char	pwd[1024];
	int		status;

	if (getcwd(pwd, 1024) == NULL)
	{
		write_gen_err_message(strerror(errno));
		return (1);
	}
	if (tokens == 0)
		status = change_dir_home(pwd, env);
	else
	{
		arg = ((t_token *)tokens->data)->str;
		if (arg[0] == '-' && arg[1] == '\0')
			status = change_to_old_dir(pwd, env);
		else if (chdir(arg) == 0)
			status = update_directories(pwd, env);
		else
		{
			write_gen_err_message(strerror(errno));
			status = EXIT_FAILURE;
		}
	}
	return (status);
}

/*
** Changes directory to home
** @param:	- [char *] directory before changing (for future OLDPWD)
**			- [t_list *] environment variable linked list pointer
** @return:	[int] exit status
** Line-by-line comments:
** @5		Function changes directory and returns 0 on success 
** @6		Function will update the environment variable linked list with the
**			new working directory values
** @7-11	Error message in case of failure
*/

int	change_dir_home(char *cur_pwd, t_list **env)
{
	int		status;
	char	*home;

	home = ft_getenv("HOME");
	if (chdir(home) == 0)
		status = update_directories(cur_pwd, env);
	else
	{
		write_gen_err_message(strerror(errno));
		status = EXIT_FAILURE;
	}
	free(home);
	home = 0;
	return (status);
}

/*
** Changes directory to the old directory
** @param:	- [char *] directory before changing (for future OLDPWD)
**			- [t_list *] environment variable linked list pointer
** @return:	[int] exit status
** Line-by-line comments:
** @13		Function will update the environment variable linked list with the
**			new working directory values
** @14-18	Error message in case of failure
*/

int	change_to_old_dir(char *cur_pwd, t_list **env)
{
	char	*old_dir;
	int		status;

	old_dir = ft_getenv("OLDPWD");
	if (!old_dir)
	{
		printf("OLDPWD not set\n");
		status = 1;
	}
	else
	{
		if (chdir(old_dir) == 0)
			status = update_directories(cur_pwd, env);
		else
		{
			write_gen_err_message(strerror(errno));
			status = EXIT_FAILURE;
		}
		free(old_dir);
		old_dir = 0;
	}
	return (status);
}
