/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:59:16 by gleal             #+#    #+#             */
/*   Updated: 2021/05/13 15:39:18 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "main.h"

/*
** File environment1.c
*/

void	replace_envs(t_list **tokens, t_list *redirs);
void	replace_env_single_token(t_token *token);
void	replace_vars_with_values(char **str);
void	replace_tilde_with_home(char **str);
void	replace_special_params(char **str);

/*
** File environment2.c
*/

char	*ft_getenv(char *key);
void	duplicate_env(t_list **dup_envp, char **envp);
void	remove_env_value(char	*key);
void	replace_status_env(char **str, int	last_status);

#endif