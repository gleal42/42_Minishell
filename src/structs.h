/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:47:10 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 10:38:02 by dda-silv         ###   ########.fr       */
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
** [int nb_cmds] number of command tables in the AST
** [int *return_value] pointer to the return_value of the last cmd_table.
**					   The pointer is set in get_cmd_table()
*/

typedef struct s_ast
{
	const char	*raw_input;
	t_list		*cmd_tables;
	int			nb_cmd_tables;
	int			*return_value;
}				t_ast;

/*
** A command table with one or more simple commands
** @fields:
** [t_list *cmds] linked list with simple commands (t_cmd *) as nodes
** [int nb_cmds] number of simple commands in the command table
** /!\ MIGHT CHANGE /!\ we might need that info per simple command 
** [char *output_file] file name after '>'
** [char *input_file] file name between '<' and '>'
** [char *error_file] file name before '>'
** /!\ MIGHT CHANGE /!\ we might need that info per simple command 
** [char *delimiter] Indicates what is separating this cmd table from the next
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
	int			nb_cmds;
	char		*output_file;
	char		*input_file;
	char		*error_file;
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
** [int nb_tokens] Number of tokens (excl. the NULL terminator)
** [char delimiter] Indicates what is separating this simple command from the next
** Potential values:
** - delimiter = '\0' (last simple command of this command table)
** - delimiter = '|' (redirect output to stdin of next simple command)
*/

typedef struct s_cmd
{
	char		**tokens;
	int			nb_tokens;
	char		delimiter;			
}				t_cmd;

#endif
