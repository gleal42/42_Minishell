/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:47:10 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/22 21:43:10 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
** A simple command with one program name and potentially arguments
** Examples:
** - ls -al dir
** - echo "Hello, World!"
** @fields:
** [char **tokens] NULL-terminated array of strings with all the tokens
** Examples: 
** - tokens[0] = "ls" / [1] = "-al" / [2] = "dir" / [3] = 0
** - tokens[1] = "echo" / [1] = "Hello, World!" / [2] = 0
** [int nb_tokens] Number of tokens (excl. the NULL terminator)
** [char split] Indicates what is separating this simple command from the next
** Potential values:
** - split = '\0' (nothing after this simple command)
** - split = '|' (redirect output)
** - split = ';' (output to stdout)
*/

typedef struct s_cmd
{
	char		**tokens;
	int			nb_tokens;
	char		split;			
}				t_cmd;

/*
** A command table with one or more simple commands.
** In case the raw_input is invalid (open quotes or finished by '|'), the raw
** input stays as first entered and all the other fields stay NULL / 0 
** @fields:
** [const char *raw_input] String entered by user in the stdin
** [t_list *cmds] linked list with simple commands (t_cmd *) as nodes
** [int nb_cmds] number of simple commands in the command table
** [char *output_file] file name after '>'
** [char *input_file] file name between '<' and '>'
** [char *output_file] file name '&>'
*/

typedef struct s_cmd_table
{
	const char	*raw_input;
	t_list		*cmds;
	int			nb_cmds;
	char		*output_file;
	char		*input_file;
	char		*error_file;
}				t_cmd_table;

#endif
