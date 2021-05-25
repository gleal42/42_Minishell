/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 09:56:37 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 09:56:42 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Gets the value stored in the environment variable linked list given a
** variable name
** @param:	- [char *] name of environment variable to check
** @return:	[char *] string duplicate of environment variable value
*/

char	*ft_getenv(char *key)
{
	int		i;
	t_list	*envp;
	char	*curr_envp;
	char	*value;

	envp = g_msh.dup_envp;
	while (envp)
	{
		i = 0;
		curr_envp = (char *)envp->data;
		while (key[i] && curr_envp[i] && (key[i] == curr_envp[i]))
			i++;
		if (!key[i] && (curr_envp[i] == '='
				|| curr_envp[i] == '\0'))
		{
			value = ft_strdup(&(curr_envp[i + 1]));
			if (!value)
				quit_program(EXIT_FAILURE);
			return (value);
		}
		envp = envp->next;
	}
	return (NULL);
}

/*
** Creates a copy of the envp string array so that it can be manipulated
** throughout our program
** @param:	- [t_list **] stored in linked list for easier exporting and
**						  unsetting (more modular memory allocation)
**			- [char **] environment vars array of strings 
**					    (third argument in main function)
** Line-by-line comments:
** @5		Some operating systems don't have the third main argument (array of
** 			environment variables). In this case the exercise would have needed
** 			to be solved using the environ extern global variable
**			(see man environ(7))
*/

void	duplicate_env(t_list **dup_envp, char **envp)
{
	t_list	*next_env;
	int		i;
	char	*tmp;

	if (!envp || !envp[0])
		quit_program(EXIT_FAILURE);
	i = 0;
	while (envp[i] != NULL)
	{
		tmp = ft_strdup(envp[i]);
		if (!tmp)
			quit_program(EXIT_FAILURE);
		next_env = ft_lstnew(tmp);
		if (!next_env)
			quit_program(EXIT_FAILURE);
		ft_lstadd_back(dup_envp, next_env);
		i++;
	}
}

/*
** In case we want to unnassign an environment variable that has been exported
** (key must be the unnassigned environment variable)
** e.g. USER=gleal receives USER to unnassign
** @param:	- [char *] environment variable name (unnassigned)
** Line-by-line comments:
** @12-16	Skip if env var is already unnassigned
*/

void	remove_env_value(char	*key)
{
	int		i;
	t_list	*envp;
	char	*curr_envp;

	envp = g_msh.dup_envp;
	while (envp)
	{
		i = 0;
		curr_envp = (char *)envp->data;
		while (key[i] && curr_envp[i] && (key[i] == curr_envp[i]))
			i++;
		if (!key[i] && curr_envp[i] == '=')
		{
			replace_string(key, &curr_envp);
			envp->data = curr_envp;
		}
		envp = envp->next;
	}
	return ;
}

/*
** Replaces token containing substr "$?" by the exit status of the last
** executed function
** @param:	- [char **] pointer to token that will be replaced
**			- [int] exit status of last exec function
*/

void	replace_status_env(char **str, int last_status)
{
	int		replace_spot;
	char	*status_string;
	char	*final;

	replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	while (replace_spot != -1)
	{
		status_string = ft_itoa(last_status);
		if (status_string == 0)
			return (quit_program(EXIT_FAILURE));
		final = replace_midstring(*str, "$?", status_string, replace_spot);
		free(status_string);
		status_string = 0;
		free(*str);
		*str = final;
		replace_spot = ft_strnstr_iterator(*str, "$?", ft_strlen(*str));
	}
}

/*
** Checks if it refers to absolute path, and if it is a file (not directory)
** @param:	- [char *] path saved in $_ variable
** @return:	[int] 1 if path is an executable, else 0
** Line-by-line comments:
** @4-5		Stat is success both for directories and files so we need to add the
**			S_ISREGularfile macro to make sure.
*/

int	is_path_executable(char *exec_file)
{
	struct stat	statbuf;

	if (has_absolute_path(exec_file)
		&& (stat(exec_file, &statbuf) == EXIT_SUCCESS
			|| S_ISREG(statbuf.st_mode)))
		return (1);
	else
		return (0);
}
