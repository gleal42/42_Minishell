/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:00:38 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/24 17:10:29 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cd.h"

/*
** Checks if environment variable value(path) is valid, printing error messages
** in case of failure
** @param:	- [char *] name of potential environment variable
** @return:	[int] exit status (0 if cd would have happened)
** Line-by-line comments:
** @6-10	In case environment variable have no values
** @13-14	In case user doesnt have permission to enter directory
** @16-17	In case there is another error entering directory
*/

int	cd_env_error_check(char *env)
{
	DIR		*dirp;
	char	*arg;
	int		status;

	arg = ft_getenv(env);
	if (arg == 0)
		status = cd_error_messsage("cd", "HOME not set");
	else if (*arg == '\0')
		status = EXIT_SUCCESS;
	else
	{
		if (!has_x_permission(arg))
			return (EXIT_FAILURE);
		dirp = opendir(arg);
		if (dirp == NULL)
			status = other_invalid_error("cd", errno, arg);
		else
		{
			status = EXIT_SUCCESS;
			closedir(dirp);
		}
		free(arg);
	}
	return (status);
}

/*
** Checks if path is valid, printing error messages in case of failure
** @param:	- [char *] relative or absolute path (argument after cd)
** @return:	[int] exit status (0 if cd would have happened)
** Line-by-line comments:
** @4-5		Case: user doesnt have permission to enter directory
** @6-7		Case: there is another error entering directory
*/

int	cd_path_error_check(char *path)
{
	DIR	*dirp;
	int	status;

	if (!has_x_permission(path))
		return (EXIT_FAILURE);
	dirp = opendir(path);
	if (dirp == NULL)
		status = other_invalid_error("cd", errno, path);
	else
	{
		status = EXIT_SUCCESS;
		closedir(dirp);
	}
	return (status);
}

/*
** Writes error message and returns EXIT_FAILURE. Thanks norm ;)
** @param:	- [char *] name of builtin to be printed in error message
** 			- [char *] error message itself
** @return:	[int] exit status (EXIT_FAILURE)
*/

int	cd_error_messsage(char *builtin, char *error)
{
	write_msh_exec_error(builtin, error);
	return (EXIT_FAILURE);
}

/*
** Writes error message based on errno and returns EXIT_FAILURE. Thanks norm ;)
** @param:	- [char *] name of builtin to be printed in error message
**			- [int] errno
**			- [char *] name of typed argument (to be displayed)
** @return:	[int] EXIT_FAILURE because it's an error message
*/

int	other_invalid_error(char *builtin, int error, char *arg)
{
	write_msh_exec_arg_error(builtin, arg, strerror(error));
	return (EXIT_FAILURE);
}

/*
** Checks if we have permission to execute path (enter in case of directory.
** Other functions have already checked it's a directory
** @param:	- [char *] absolute or relative directory path
** @return:	[int] 1 if true
** Line-by-line comments:
** @5		Mask user execute permission is non zero in case it
** 			exists in the path
*/

int	has_x_permission(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == EXIT_SUCCESS)
	{
		if (statbuf.st_mode & S_IXUSR)
			return (1);
		else
		{
			write_msh_exec_arg_error("cd", path, "Permission denied");
			return (0);
		}
	}
	else
	{
		write_msh_exec_arg_error("cd", path, strerror(errno));
		return (0);
	}
}
