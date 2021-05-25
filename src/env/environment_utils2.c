/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:04:11 by gleal             #+#    #+#             */
/*   Updated: 2021/05/25 11:27:02 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_utils.h"

/*
** In a string of type VAR=VALUE, it extracts the VALUE
** @param:	- [char *] string to be analyzed
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

/*
** After replacing $ENVVAR, it confirms token is now empty string
** @param:	- [void *] pointer to token struct
** @return:	[int] true if token is empty string
*/

int	is_token_empty(void *data)
{
	int		check;
	char	*token;

	token = data;
	if (*token == '\0')
		check = 1;
	else
		check = 0;
	return (check);
}

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

/*
** Updates SHLVL environment variable everytime we call ./minishell inside
** another ./minishell
** Line-by-line comments:
** @4-5		in case variable is unset we create it and set it to 1
** @7-17	in case variable is set we increment 1 everytime we call 
**			./minishell
*/

void	increment_shlvl(void)
{
	char	*cur_lvl;
	int		lvl_nbr;

	if (is_env_var("SHLVL", g_msh.dup_envp) == 0)
		create_environment_var("SHLVL=1", &g_msh.dup_envp);
	else
	{
		cur_lvl = ft_getenv("SHLVL");
		lvl_nbr = ft_atoi(cur_lvl);
		lvl_nbr++;
		free(cur_lvl);
		cur_lvl = ft_itoa(lvl_nbr);
		if (cur_lvl == 0)
			quit_program(EXIT_FAILURE);
		update_environment_var("SHLVL", cur_lvl, g_msh.dup_envp);
		free(cur_lvl);
	}
}
