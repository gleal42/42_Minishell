/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:04:11 by gleal             #+#    #+#             */
/*   Updated: 2021/05/16 18:49:20 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_utils.h"

/*
** In a string of type VAR=VALUE it extracts the VALUE
** @param:	- [char *] string to be analyzed
**			- [type] param_value
** @return:	[char *] string duplicate of value
** Line-by-line comments:
** @11		One more to compensate for the equal sign
*/

char	*get_value_name(char *str)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && !is_token_delimiter(str[i]) && str[i] != '$'
		&& str[i] != '=')
		i++;
	i++;
	len = ft_strlen(str) - i;
	value = ft_substr(str, i, len);
	if (!value)
		quit_program(EXIT_FAILURE);
	return (value);
}

// /*
// ** After replacing $ENVVAR, it confirms token is now empty string
// ** @param:	- [void *] pointer to token struct
// ** @return:	[int] true if token is empty string
// */

// int	is_token_empty(void *data)
// {
// 	int		check;
// 	t_token	*token;

// 	token = data;
// 	if (*token->str == '\0' && token->delimiter == ' ')
// 		check = 1;
// 	else
// 		check = 0;
// 	return (check);
// }

/*
** OLDPWD variable starts as an unset variable. This function creates it in
** case it doesn't exist or updates it in case it exists, making sure it is
** empty
** Line-by-line comments:
** @1-2		Create environment variable in case it doesn't exist
** @3-4 	In case environment variable is set we update it to delete value
*/

void	unset_oldpwd(void)
{
	if (is_env_var("OLDPWD", g_msh.dup_envp) == 0)
		create_environment_var("OLDPWD", &g_msh.dup_envp);
	else
		remove_env_value("OLDPWD");
}

/*
** Replace string in destination with string duplicate of source string
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
