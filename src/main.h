/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:48:16 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/21 15:20:29 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <sys/wait.h>

# include "../libft/src/libft.h"
# include "structs.h"
# include "constants.h"
# include "utils.h"
# include "shell_subsystems.h"

void	write_prompt(void);
int		get_cmd(t_cmd_table **cmd_table);
int		execute_cmd(t_cmd_table *cmd_table);

#endif
