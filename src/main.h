/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:48:16 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 10:25:37 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <string.h>
# include <fcntl.h>
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

# include "builtin_utils.h"
# include "ft_cd.h"
# include "ft_exit.h"
# include "ft_echo.h"
# include "ft_env.h"
# include "ft_pwd.h"
# include "ft_export.h"
# include "ft_unset.h"

# include "environment.h"
# include "environment_utils.h"

# include "utils.h"
# include "signals.h"

# include "free_memory.h"
# include "exit_prog.h"

# include "termcaps.h"

# include "parse.h"
# include "get_input.h"
# include "parse_utils.h"
# include "input_validation.h"

# include "execute.h"
# include "execute_utils.h"
# include "fork_exec_wait.h"
# include "redirections_pipes.h"
# include "get_absolute_path.h"

t_msh	g_msh;

void	init_minishell(t_msh *msh, char **envp);
void	catch_signals(int signum);
void	test_minishell(char *test, char **envp);

#endif
