/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:48:16 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/07 19:16:27 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <string.h>
# include <curses.h>
# include <termcap.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>

# include "../libft/src/libft.h"

# include "structs.h"
# include "constants.h"
# include "utils.h"
# include "signals.h"

# include "free_memory.h"
# include "ft_exit.h"

# include "termcaps.h"

# include "parse.h"
# include "get_input.h"
# include "parse_utils.h"
# include "input_validation.h"

# include "execute.h"
# include "execute_utils2.h"
# include "execute_program_utils.h"
# include "environment.h"
# include "builtins.h"

/*
** TO DELETE WHEN PROJECT FINISHED
*/

# include "print_ast.h"

/*
** TO DELETE WHEN PROJECT FINISHED
*/

t_msh	g_msh;

void	init_minishell(t_msh *msh, char **envp);
void	catch_signals(int signum);

#endif
