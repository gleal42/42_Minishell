/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 20:17:08 by gleal             #+#    #+#             */
/*   Updated: 2021/04/26 21:18:26 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

int		has_repeated_char_in_str(char repeat_chr, char *str, unsigned int start);
char	*get_env_value(char *var, t_list *env);

#endif
