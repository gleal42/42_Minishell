/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:59:16 by gleal             #+#    #+#             */
/*   Updated: 2021/04/30 17:43:53 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "main.h"
# include "parse_utils.h"

int		replace_vars_with_values(char **str);
char	*get_var_name(char *str);
int		update_token(char **token_before, int *start, char *value, int var_len);
char	*update_token_before(char *token_before, int *start, char *value);
char	*update_token_after(char *token_before, int *start,
			char *temp, int var_len);
int		replace_tilde_with_home(char **str);
int		tilde_join(char **str, char **home_path);

#endif