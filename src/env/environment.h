/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:59:16 by gleal             #+#    #+#             */
/*   Updated: 2021/05/03 00:24:15 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "main.h"
# include "parse_utils.h"

/*
** File environment.c
*/

void	env_vars(t_list	*tokens, int last_status);
void	replace_vars_with_values(char **str);
void	replace_tilde_with_home(char **str);
void	replace_special_params(char **str, int last_status);

/*
** File environment_utils.c
*/

int		is_env_var(char *potential_var, t_list *env);
char	*get_var_name(char *str);
int		ft_strnstr_iterator(char *haystack, char *needle, size_t len);
char	*replace_midstring(char *original, char *old_substr,
			char *new_substr, int replace_i);
void	tilde_join(char **str, char **home_path);

#endif