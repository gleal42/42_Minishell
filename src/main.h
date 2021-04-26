/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:48:16 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/26 11:22:28 by dda-silv         ###   ########.fr       */
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
# include "shell_subsystems.h"
# include "cmd_history.h"

/*
** TO DELETE WHEN PROJECT FINISHED
*/

# include "print_ast.h"

/*
** TO DELETE WHEN PROJECT FINISHED
*/

void	write_prompt(void);
t_ast	*get_ast(void);
int		execute_cmd(t_ast *ast);

#endif
