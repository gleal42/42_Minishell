/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:53:43 by gleal             #+#    #+#             */
/*   Updated: 2021/05/25 10:45:02 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_utils.h"

/*
** Checks if first token is one of the mandatory builtin programs
** @param:	- [char *] token to be checked
** @return:	[int] true or false
*/

int	is_builtin(t_list *tokens)
{
	int		check;
	char	*program_name;

	program_name = tokens->data;
	if (ft_strcmp(program_name, "exit") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "echo") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "env") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "cd") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "pwd") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "export") == 0)
		check = 1;
	else if (ft_strcmp(program_name, "unset") == 0)
		check = 1;
	else
		check = 0;
	return (check);
}

/*
** Converts a linked list to a NULL-terminated array of strings
** @param:	- [t_list *] list with string as data
** @return:	[char **] NULL-terminated array of strings
*/

char	**convert_list_to_arr(t_list *lst)
{
	char	**strs;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(lst);
	strs = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		strs[i++] = (char *)lst->data;
		lst = lst->next;
	}
	return (strs);
}

/*
** Checks if the first token has a relative path like ./a.out or ./minishell
** @param:	- [char *] first token of the simple command. Likely to represent
**                     the program name
** @return:	[int] true or false
*/

int	has_relative_path(char *first_token)
{
	int	check;

	if (*first_token == '.')
		check = 1;
	else
		check = 0;
	return (check);
}

/*
** Checks if the first token has a absolute path like /bin/ls
** @param:	- [char *] first token of the simple command. Likely to represent
**                     the program name
** @return:	[int] true or false
*/

int	has_absolute_path(char *first_token)
{
	int	check;

	if (*first_token == '/')
		check = 1;
	else
		check = 0;
	return (check);
}
