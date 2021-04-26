/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:59:48 by gleal             #+#    #+#             */
/*   Updated: 2021/04/26 23:13:23 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

int		ft_cd(char **args, t_list **env)
{
	char	buf[1024];
	char	*home;
//	char	*adj_path;

	home = get_env_value("HOME", *env);
	if (!args[0])
		chdir(home);
	/*else
	{
		adj_path = adjust_path(args[0], home);*/
		chdir(args[0]);
//	}
	getcwd(buf, 1024);
	printf("%s\n", buf);
	return(0);
}

/*char	*adjust_path(args[0], home)
{

}*/
