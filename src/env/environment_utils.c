/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:17:53 by gleal             #+#    #+#             */
/*   Updated: 2021/04/28 19:14:02 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "environment.h"

int		is_env_var(char *potential_var, t_list *env)
{
	int		i;
	char	*env_str;

	while (env)
	{
		i = 0;
		env_str = (char *)env->data;
		while (potential_var[i] && env_str[i] && (potential_var[i] == env_str[i]))
			i++;
		if ((potential_var[i] == 0 || ft_isspace(potential_var[i])) && env_str[i] == '=')
			return (i);
		env = env->next;
	}
	return (0);
}