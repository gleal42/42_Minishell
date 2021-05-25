/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:47:10 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 10:21:36 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
** An Abstract Syntax Tree (aka AST) that gathers one or more command tables.
** The AST is only created if the input is valid (passed is_input_valid()).
** We know this struct won't win any awards for most useful struct... but it's
** here for readability purposes
** @fields:
** [t_list *cmd_tables] linked list with command tables (t_cmd_table *) as nodes
*/

typedef struct s_ast
{
	t_list			*cmd_tables;
}				t_ast;

/*
** A command table with one or more simple commands
** @fields:
** [t_list *cmds] linked list with simple commands (t_cmd *) as nodes
** [char *delimiter] Indicates what is separating this cmd table from the next
** Potential values:
** - delimiter = "\0" (last command table)
** - delimiter = ";" (consecutive execution of the next cmd table)
** - delimiter = "||" (execution of the next cmd table only if the previous has
** a falsy exit_status)
** - delimiter = "&&"" (execution of the next cmd table only if the previous has
** a truthy exit_status)
** [int nb_cmds] number of simple commands in cmds linked list]
** [int **pipes] 2D array of ints. Each subarray is a pipe
** [t_list *pids] linked list of pid. Works as a queue / FIFO data structure.
** Each time we fork(), we add a node at the back. We wait on dead child
** processses as long the queue is not empty
** [int return_value] return value of this specific command table. We also have
** t_msh an exit_status field for that intent. But we need to make sure we don't
** ignore return value of builtin functions (like cd), if they finish first than
** forks like:
** - "sleep 5 | cd wrong_folder", cd would set error because wrong direction but
** sleep would execute correctly. So cd sets the exit_status not sleep
*/

typedef struct s_cmd_table
{
	t_list			*cmds;
	char			*delimiter;
	int				nb_cmds;
	int				**pipes;
	t_list			*pids;
	int				return_value;
}				t_cmd_table;

/*
** A simple command with one program name and potentially one or more arguments
** Examples:
** - ls -al dir
** - echo "Hello, World!"
** @fields:
** [t_list *tokens] linked list with all the tokens of the simple command
** Examples: 
** - 1st node: "ls" / 2nd node: "-al" / 3rd node: "dir"
** - 1st node: "echo" / 2nd node: "Hello, World!"
** [t_list *redirs] linked list with all the redirections (t_redir *) targeting
** this simple command
*/

typedef struct s_cmd
{
	t_list		*tokens;
	t_list		*redirs;
}				t_cmd;

/*
** A single redirection targeting a simple command
** @fields:
** [t_token *direction] name of file and delimiter enclosing token
** [char type[2]] type of redirection.
** Potential values:
** - ">"  - redirect stdout (for files: also overwrite file's content)
** - ">>" - redirect stdout (for files: also append to file's content)
** - "<"  - redirect stdin
*/

typedef struct s_redir
{
	char			*direction;
	char			type[2];
}				t_redir;

/*
** Settings of the terminal and a few capabilties from the termcaps lib
** @fields:
** [struct termios old_term] default terminal settings (i.e. canonical mode).
** This struct is set in the termios lib
** [struct termios new_term] modified terminal settings (i.e. non-canonical
** mode)
** [char *buffer] the termcaps capabilities require a buffer to be passed to
** various functions like tgetent or tgetstr
** [char *keys_on] set keypad functionalities
** [char *keys_off] turn off keypad functionalities. Required at end of program
** [char *up_arrow] value that the terminal will return when pressing up arrow
** [char *down_arrow] value that the terminal will return when pressing down
** arrow
** [char *backspace] value that the terminal will return when pressing backspace
** [char *del_line] capability that allows to delete the content of the line
** where the cursor currently is positioned
** [char *set_cursor_begin] sets the cursor to the beginning of the current line
*/

typedef struct s_termcaps
{
	struct termios	old_term;	
	struct termios	new_term;	
	char			*buffer;
	char			*keys_on;
	char			*keys_off;
	char			*up_arrow;
	char			*down_arrow;
	char			*backspace;
	char			*del_line;
	char			*set_cursor_begin;
}				t_termcaps;

/*
** Global struct that carries all data used throughout the program
** @fields:
** [t_dlist *] double linked list with each node representing a previously
** entered input
** [t_ast *] struct with the abstract syntax tree
** [t_termcaps] struct with the settings of the termical and a few capabilities
** [t_list *] the duplicate of environment variables. Each node is a string
** [int exit_status] exit_status of the last simple command that ran
** [t_cmd_table *curr_cmd_table] points to the cmd_table being currently
** executed. This is useful for when the exit program name is used alongside
** other simple commands we don't have to exit, otherwise we do
*/

typedef struct s_msh
{
	t_dlist			*input_history;
	t_ast			*ast;
	t_termcaps		termcaps;
	t_list			*dup_envp;
	int				exit_status;
	t_cmd_table		*curr_cmd_table;
}				t_msh;

#endif
