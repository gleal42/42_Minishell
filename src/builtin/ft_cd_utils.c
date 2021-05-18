/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:34:36 by gleal             #+#    #+#             */
/*   Updated: 2021/05/17 01:39:48gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cd.h"

/*
** checks if environment variable value(path) is valid, printing
** error messages in case of failure
** @param:	- [char *] name of potential environment variable
** @return:	[int] exit status (0 if cd would have happened)
** Line-by-line comments:
** @6-10	in case environment variable have no values
** @13-14	in case user doesnt have permission to enter directory
** @16-17	in case there is another error entering directory
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
** checks if path is valid, printing error messages in case of failure
** @param:	- [char *] relative or absolute path (argument after cd)
** @return:	[int] exit status (0 if cd would have happened)
** Line-by-line comments:
** @4-5	in case user doesnt have permission to enter directory
** @6-7	in case there is another error entering directory
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
** error message for when there are too many arguments after cd
** @param:	- [char *] name of builtin to be printed in error message
** @return:	[int] exit status (EXIT_FAILURE)
*/

int	cd_error_messsage(char *builtin, char *error)
{
	write_msh_exec_error(builtin, error);
	return (EXIT_FAILURE);
}

/*
** prints message based on errno (received as error int)
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
** checks if we have permission to execute path (enter in case 
of directory. Other functions have already checked its a directory
** @param:	- [char *] absolute or relative directory path
** @return:	[int] 1 if true
** Line-by-line comments:
** @5	mask User execute permission is non zero in case it 
** 		exists in the path
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
