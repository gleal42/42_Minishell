/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:59:16 by gleal             #+#    #+#             */
/*   Updated: 2021/05/11 12:43:27 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "main.h"
# include "parse_utils.h"

/*
** File environment1.c
*/

void	replace_env_in_tokens(t_list **tokens);
void	replace_vars_with_values(char **str);
void	replace_tilde_with_home(char **str);
void	replace_special_params(char **str, int last_status);

/*
** File environment2.c
*/

char	*ft_getenv(char *key);
void	duplicate_env(t_list **dup_envp, char **envp);

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