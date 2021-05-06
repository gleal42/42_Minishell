/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program_utils.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:47:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/06 12:59:20 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_PROGRAM_UTILS_H
# define EXECUTE_PROGRAM_UTILS_H

# include "main.h"

int		has_relative_path(char *first_token);
char	*get_absolute_path(char *program_name);
char	**get_path_env_split(void);
char	*get_correct_path(char *program_name, char **path_env_split);
void	add_slash(char ***path_env_split);

#endif
