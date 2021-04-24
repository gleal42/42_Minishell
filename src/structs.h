/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:47:10 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 21:06:33 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
** An Abstract Syntax Tree (aka AST) that gathers one or more command tables
** In case the raw_input is invalid, the raw input stays as first entered and
** all the other fields stay NULL / 0 and execute_cmd is not called
** @fields:
** [const char *raw_input] string entered by user in stdin
** [t_list *cmd_tables] linked list with command tables (t_cmd_table *) as nodes
** [int *return_value] pointer to the return_value of the last cmd_table.
**					   The pointer is set in get_cmd_table()
*/

typedef struct s_ast
{
	const char	*raw_input;
	t_list		*cmd_tables;
	int			*return_value;
}				t_ast;

/*
** A command table with one or more simple commands
** @fields:
** [t_list *cmds] linked list with simple commands (t_cmd *) as nodes
** [int nb_cmds] number of simple commands in the command table
** [char delimiter[2]] Indicates what is separating this cmd table from the next
** Potential values:
** - delimiter = "\0" (last command table)
** - delimiter = ";" (consecutive execution of the next cmd table)
** - delimiter = "||" (OR operator)
** - delimiter = "&&"" (AND operator)
** [int return_value] Return value of this cmd table. Useful for && and ||
*/

typedef struct s_cmd_table
{
	t_list		*cmds;
	char		delimiter[2];
	int			return_value;
}				t_cmd_table;

/*
** A simple command with one program name and potentially one or more arguments
** Examples:
** - ls -al dir
** - echo "Hello, World!"
** @fields:
** [char **tokens] NULL-terminated array of strings with all the tokens
** Examples: 
** - tokens[0] = "ls" / [1] = "-al" / [2] = "dir" / [3] = 0
** - tokens[1] = "echo" / [1] = "Hello, World!" / [2] = 0
** [t_list *redirs] linked list with all the redirections (t_redir *) targeting
** this simple command
*/

typedef struct s_cmd
{
	char		**tokens;
	t_list		*redirs;
}				t_cmd;

/*
** A single redirection targeting a simple command
** @fields:
** [char *direction] name of file or executable
** [char type[2]] type of redirection.
** Potential values:
** - ">"  - redirect stdout (for files: also overwrite file's content)
** - ">>" - redirect stdout (for files: also append to file's content)
** - "<"  - redirect stdin
** [int is_file] true or false. If is file, simply redirect.
**				 Else, execute & redirect
** Examples:
** - direction = "file1.txt" / type = ">" / int = 1
** - direction = "ls" / type = "<" / int = 0
*/

typedef struct s_redir
{
	char		*direction;
	char		type[2];
	int			is_executable;
}				t_redir;

#endif
