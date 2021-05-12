/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:59:16 by gleal             #+#    #+#             */
/*   Updated: 2021/05/12 09:17:23 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_UTILS_H
# define ENVIRONMENT_UTILS_H

# include "main.h"

/*
** File environment_utils.c
*/

int		is_env_var(char *potential_var, t_list *env);
char	*get_var_name(char *str);
int		ft_strnstr_iterator(char *haystack, char *needle, size_t len);
char	*replace_midstring(char *original,
			char *old_substr,
			char *new_substr,
			int replace_i);
void	tilde_join(char **str, char **home_path);

/*
** File environment_utils2.c
*/

char	*get_value_name(char *str);
int		is_token_empty(void *data);

#endif
