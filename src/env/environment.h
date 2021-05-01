/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:59:16 by gleal             #+#    #+#             */
/*   Updated: 2021/05/01 22:58:23 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "main.h"
# include "parse_utils.h"

/*
** File environment.c
*/

void	replace_vars_with_values(char **str);
void	replace_tilde_with_home(char **str);

/*
** File environment_utils.c
*/

char	*get_var_name(char *str);
void	update_token(char **token_before, int *start, char *value, int var_len);
char	*update_token_before(char *token_before, int *start, char *value);
char	*update_token_after(char *token_before, int *start,
						char **temp, int var_len);

/*
** File environment_utils2.c
*/

void	tilde_join(char **str, char **home_path);

#endif