/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/10 14:52:16 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
** Extracts the Abstract Syntax Tree (AST) out of the input entered in cmd line.
** In this case, the AST is a list that has a cmd_table per node and each
** cmd_table has a list a simple command per node. Each simple command has a 
** list of tokens
** @return:	[t_ast *] struct with input, list of cmd_tables and a pointer
**					  to a return value
** Line-by-line comments:
** @8		For further use (history), we need to keep the input unchanged
**			and stored in the struct
** @14		We pass down the reference of the curr_pos to keep track of the
** 			parsing executed by every subsequent function
** @17		In execute(), we'll want to execute the cmd_table in entering order
**			so we need to add to the back each new cmd_table
** @19		ast->return_value now points to the return_value of the last
**			cmd_table. It makes assigning the value to $? easier
*/

t_ast	*get_ast(const char *input)
{
	t_ast	*ast;
	t_list	*cmd_table;
	int		curr_pos;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		exit_prog(EXIT_FAILURE);
	curr_pos = 0;
	while (input[curr_pos])
	{
		cmd_table = ft_lstnew((void *)get_cmd_table(input, &curr_pos));
		if (!cmd_table)
			exit_prog(EXIT_FAILURE);
		ft_lstadd_back(&ast->cmd_tables, cmd_table);
	}
	ast->return_value = &((t_cmd_table *)cmd_table->data)->return_value;
	return (ast);
}

/*
** Gets a command table, which is a series of simple commands to execute
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
** @return:	[t_cmd_table *] struct with list of simple cmds, the delimiter that
** 						  seperates this cmd_table from the next and the
**						  return value of this process
** Line-by-line comments:
** @13-14	If the delimiter is '|', it means we just got a simple command
**			and we are about to get a new one. So we increment curr_pos and we
**			continue parsing
**			All error handling is done before by is_input_valid() so we don't
**			need to be on the lookout for bad syntax
** @15-20	If the delimiter is ';', the current cmd_table is finished
*/

t_cmd_table	*get_cmd_table(const char *input, int *curr_pos)
{
	t_cmd_table	*cmd_table;
	t_list		*cmd;

	cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	if (!cmd_table)
		exit_prog(EXIT_FAILURE);
	while (input[*curr_pos])
	{
		skip_spaces(input, curr_pos);
		cmd = ft_lstnew((void *)get_cmd(input, curr_pos));
		if (!cmd)
			exit_prog(EXIT_FAILURE);
		ft_lstadd_back(&cmd_table->cmds, cmd);
		if (input[*curr_pos] == '|')
			(*curr_pos)++;
		else if (input[*curr_pos] == ';')
		{
			*cmd_table->delimiter = ';';
			(*curr_pos)++;
			break ;
		}
	}
	return (cmd_table);
}

/*
** Gets a simple command, which is a series of tokens
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
** @return:	[t_cmd *] struct with an arr of tokens (i.e. strings) and a list
**                    of redirection in order of entering
** Line-by-line comments:
** @8		A simple command can be delimited by ';', '|', "||" or "&&". While
**			we don't see those, it means we still are on the same simple command
**			Redirection case: we count '>' and '<' as delimiter to stop the loop
**			but only to call get_redirs right after. So we are still in a
**			simple command if we find '<' or '>'
*/

t_cmd	*get_cmd(const char *input, int *curr_pos)
{
	t_cmd	*cmd;
	t_list	*new_node;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		exit_prog(EXIT_FAILURE);
	while (input[*curr_pos] && input[*curr_pos] != ';'
			&& input[*curr_pos] != '|')
	{
		if (input[*curr_pos] != '>' && input[*curr_pos] != '<')
		{
			new_node = ft_lstnew((void *)get_token(input, curr_pos));
			if (!new_node)
				exit_prog(EXIT_FAILURE);
			ft_lstadd_back(&cmd->tokens, new_node);
		}
		else if (input[*curr_pos] == '>' || input[*curr_pos] == '<')
		{
			new_node = ft_lstnew((void *)get_redir(input, curr_pos));
			if (!new_node)
				exit_prog(EXIT_FAILURE);
			ft_lstadd_back(&cmd->redirs, new_node);
		}
	}
	return (cmd);
}

/*
** Gets a token, which represent one argument in the cmd_line. It can
** either be a word or a string of words if quotes are used.
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
** @return:	[t_token *] a struct with a str and a char delimiter
** Line-by-line comments:
** @7		The delimiter can be a space, single or double quotes.
**			get_delimiter() increments curr_pos if a quotes is found so that
**			the token starts after the quotes
** @8		We need to save the beginning of the token so that we can extract
**			the string once we have found the end of the token
** @11-12	The token is a string of words because a quote has been found
**			by get_delimiter(). So we parse while we haven't found it's matching
**			quote (either single or double)
** @13-14	The token is a word and will be finished when we find a delimiter
**			(' ', ';', '|', ,'&', '<' or '>')
** @20-21	We need to do one last increment of curr_pos if we were dealing with
**			quotes, otherwise next time get_token() will be called it will
**			process the closing quotes of this token as the opening ones of the
**			next token
** 22-23	If the delimiter is a space, a valid input would be:
**			hello"wor'ld"'te"st'
**			This input needs to represent 1 single token and be interpreted as:
**			hellowor'ldte"st
*/

t_token	*get_token(const char *input, int *curr_pos)
{
	t_token	*token;
	int		saved_pos;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		exit_prog(EXIT_FAILURE);
	token->delimiter = get_delimiter(input, curr_pos);
	saved_pos = *curr_pos;
	while (input[*curr_pos])
	{
		if (token->delimiter != ' ' && input[*curr_pos] == token->delimiter)
			break ;
		else if (is_delimiter(input[*curr_pos]))
			break ;
		(*curr_pos)++;
	}
	token->str = ft_substr(input, saved_pos, *curr_pos - saved_pos);
	if (!token->str)
		exit_prog(EXIT_FAILURE);
	if (token->delimiter != ' ')
		(*curr_pos)++;
	else if (token->delimiter == ' ')
		delete_quotes(token->str);
	skip_spaces(input, curr_pos);
	return (token);
}

/*
** Gets a single redirection
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the input  
** @return:	[t_redir *] struct with a string with the direction and the type
** Line-by-line comments:
** @6-14	Gets the type
** @16		Gets the file
*/

t_redir	*get_redir(const char *input, int *curr_pos)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		exit_prog(EXIT_FAILURE);
	if (input[*curr_pos] == '<')
		*redir->type = input[(*curr_pos)++];
	else if (!ft_strncmp(&input[*curr_pos], ">>", 2))
	{
		ft_strncpy(redir->type, (char *)&input[*curr_pos], 2);
		*curr_pos += 2;
	}
	else if (input[*curr_pos] == '>')
		*redir->type = input[(*curr_pos)++];
	skip_spaces(input, curr_pos);
	redir->direction = get_token(input, curr_pos);
	return (redir);
}
