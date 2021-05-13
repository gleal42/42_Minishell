/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:04:11 by gleal             #+#    #+#             */
/*   Updated: 2021/05/13 19:46:47 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_utils.h"

/*
** In a string of type VAR=VALUE it extracts the VALUE
** @param:	- [char *] string to be analyzed
**			- [type] param_value
** @return:	[char *] string duplicate of value
** Line-by-line comments:
** @11	one more to compensate for the equal sign
*/

char	*get_value_name(char *str)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && !is_delimiter(str[i]) && str[i] != '$'
		&& str[i] != '=')
		i++;
	i++;
	len = ft_strlen(str) - i;
	value = ft_substr(str, i, len);
	if (!value)
		quit_program(EXIT_FAILURE);
	return (value);
}

/*
** After replacing $ENVVAR, it confirms token is now empty string
** @param:	- [void *] pointer to token struct
** @return:	[int] true if token is empty string.
** Line-by-line comments:
*/

int	is_token_empty(void *data)
{
	int		check;
	t_token	*token;

	token = data;
	if (*token->str == '\0' && token->delimiter == ' ')
		check = 1;
	else
		check = 0;
	return (check);
}

/*
** OLDPWD variable starts as an unset variable. This function creates it
in case it doesn't exist or updates it in case it exists, making sure 
it is empty.
** Line-by-line comments:
** @1-2	create environment variable in case it doesn't exist.
** @3-4 in case environment variable is set we update it to delete value.
*/

void	unset_oldpwd(void)
{
	if (is_env_var("OLDPWD", g_msh.dup_envp) == 0)
		create_environment_var("OLDPWD", &g_msh.dup_envp);
	else
		remove_env_value("OLDPWD");
}

/*
** replace string in destination with string duplicate of source string
*/

void	replace_string(char *src, char **dest)
{
	char	*temp;

	temp = ft_strdup(src);
	if (temp == 0)
		quit_program(EXIT_FAILURE);
	free(*dest);
	*dest = 0;
	*dest = temp;
}

char	*get_path_dir(char *path)
{
	int	len;
	int	i;
	char	*dir_path;

	len = ft_strlen(path);
	i = len - 1;
	if (ft_strchr(path, '/') == 0)
		return (0);
	while (i >= 0 && path[i] == '/')
		i--;
	while (i >= 0 && path[i] != '/')
		i--;
	while (i - 1 >= 0 && path[i - 1] == '/')
		i--;
	if (i > 0)
	{
		dir_path = ft_substr(path, 0, i);
		if (dir_path == 0)
			quit_program(EXIT_FAILURE);
	}
	return (0);
}
