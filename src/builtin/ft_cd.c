/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:59:48 by gleal             #+#    #+#             */
/*   Updated: 2021/04/27 19:30:57 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

int		ft_cd(char **args)
{
	char	buf[1024];
	char	*home;
//	char	*adj_path;

	home = ft_getenv("HOME");
/*	if (args[0] == 0)
	{
		if(chdir(home) == 0)
 		update_directories(&home, env);
	}
	else
	{
		if (args[0][0] == '-' && args[0][1] == 0)
		*/	
	chdir(args[0]);
	getcwd(buf, 1024);
	printf("%s\n", buf);
	return(0);
}

/*void	*update_directories(char *new_workdir, t_list **env)
{
	char	*old_pwd;

	if (is_env_var("OLDPWD", *env))
	{
		old_pwd = malloc(sizeof(char) * 7);
		old_pwd = ft_strcpy(old_pwd, "OLDPWD");
		replace_var_with_value(&old_pwd, "OLDPWD", *env);
	}

	return (0);
}*/
