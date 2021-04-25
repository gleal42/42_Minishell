/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 10:14:41 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
** Extracts the Abstract Syntax Tree (AST) out of the input entered in cmd line.
** In this case, the AST is a list that has a cmd_table per node and each
** cmd_table has a list a simple command per node. Each simple command has a 
** NULL-terminated array of strings representing a token.
** @param:	- [type] param_value
**			- [type] param_value
** @return:	[t_ast *] struct with raw_input, list of cmd_tables and a pointer
**					  to a return value
** Line-by-line comments:
** @8		For further use (history), we need to keep the raw_input unchanged
**			and stored in the struct
** @14		We pass down the reference of the curr_pos to keep track of the
** 			parsing executed by every subsequent function
** @17		In execute(), we'll want to execute the cmd_table in entering order
**			so we need to add to the back each new cmd_table
** @19		ast->return_value now points to the return_value of the last
**			cmd_table. It makes assigning the value to $? easier
*/

t_ast	*get_ast(void)
{
	t_ast	*ast;
	t_list	*cmd_table;
	int		curr_pos;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		exit(EXIT_FAILURE);
	ast->raw_input = get_raw_input();
	if (!is_input_valid(ast->raw_input))
		return (ast);
	curr_pos = 0;
	while (ast->raw_input[curr_pos])
	{
		cmd_table = ft_lstnew((void *)get_cmd_table(ast->raw_input, &curr_pos));
		if (!cmd_table)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&ast->cmd_tables, cmd_table);
	}
	ast->return_value = &((t_cmd_table *)cmd_table->data)->return_value;
	return (ast);
}

/*
** Gets the characters entered in the command line by user. Multiline commands
** aren't supported so we only call get_next_line once
** @return:	[char *] line entered without any alterations nor checks
*/

char	*get_raw_input(void)
{
	char	*raw_input;

	if (get_next_line(STDIN_FILENO, &raw_input) == -1)
		exit(EXIT_FAILURE);
	return (raw_input);
}

/*
** Gets a command table, which is a series of simple commands to execute
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the raw_input  
** @return:	[t_cmd_table] struct with list of simple cmds, the delimiter that
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

t_cmd_table	*get_cmd_table(const char *raw_input, int *curr_pos)
{
	t_cmd_table	*cmd_table;
	t_list		*cmd;

	cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	if (!cmd_table)
		exit(EXIT_FAILURE);
	while (raw_input[*curr_pos])
	{
		cmd = ft_lstnew((void *)get_cmd(raw_input, curr_pos));
		if (!cmd)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&cmd_table->cmds, cmd);
		if (raw_input[*curr_pos] == '|')
			(*curr_pos)++;
		else if (raw_input[*curr_pos] == ';')
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
**			- [int *] the current parsing position within the raw_input  
** @return:	[t_cmd *] struct with an arr of tokens (i.e. strings) and a list
**                    of redirection in order of entering
** Line-by-line comments:
** @10		A simple command can be delimited by ';', '|', "||" or "&&". While
**			we don't see those, it means we still are on the same simple command
**			Redirection case: we count '>' and '<' as delimiter to stop the loop
**			but only to call get_redirs right after. So we are still in a
**			simple command if we find '<' or '>'
** @20		While parsing and gathering tokens, we work with lists because it's
**			more convenient to append a new one. But as the execve() function
**			takes a NULL-terminated array of strings we convert to that format
**			before returning the simple command
*/

t_cmd	*get_cmd(const char *raw_input, int *curr_pos)
{
	t_cmd	*cmd;
	t_list	*lst_tokens;
	t_list	*token;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		exit(EXIT_FAILURE);
	skip_spaces(raw_input, curr_pos);
	lst_tokens = 0;
	while (raw_input[*curr_pos] && !is_delimiter(raw_input[*curr_pos]))
	{
		token = ft_lstnew((void *)get_token(raw_input, curr_pos));
		if (!token)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&lst_tokens, token);
		skip_spaces(raw_input, curr_pos);
	}
	if (raw_input[*curr_pos] == '>' || raw_input[*curr_pos] == '<')
		cmd->redirs = get_redirs(raw_input, curr_pos);
	cmd->tokens = convert_list_to_arr(&lst_tokens);
	return (cmd);
}

/*
** Gets a token, which represent one argument in the cmd_line. It can
** either be a word or a string of words if quotes are used
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the raw_input  
** @return:	[char *] the token
** Line-by-line comments:
** @6		set_token() will set the values	of has_dquotes_open and
**			has_squotes_open according to the first char of the piece of str
**			(i.e. raw_input[*curr_pos]). It will also increment curr_pos if
**			a quote is found
** @7		We need to save the beginning of the token so that we can extract
**			the string once we have found the end of the token
** @10-16	We have to distinct cases here:
** @10-14	- The token is a string of words because a quote has been found
**			by set_quotes(). So we parse while we haven't found it's matching
**			quote (either single or double)
** @15-16	- The token is a word and will be finished when we find a delimiter
**			(' ', ';', '|', ,'&', '<' or '>')
** @22-23	We need to do one last increment of curr_pos if we were dealing with
**			quotes, otherwise next time get_token() will be called it will
**			process the closing quotes of this token as the opening ones of the
**			next token
*/

char	*get_token(const char *raw_input, int *curr_pos)
{
	char	*token;
	int		has_dquotes_open;
	int		has_squotes_open;
	int		saved_pos;

	set_quotes(raw_input, curr_pos, &has_dquotes_open, &has_squotes_open);
	saved_pos = *curr_pos;
	while (raw_input[*curr_pos])
	{
		if ((raw_input[*curr_pos] == '"' && has_dquotes_open)
			|| (raw_input[*curr_pos] == '\'' && has_squotes_open))
			break ;
		else if ((has_dquotes_open || has_squotes_open) && ++(*curr_pos))
			continue ;
		else if (is_delimiter(raw_input[*curr_pos]))
			break ;
		(*curr_pos)++;
	}
	token = ft_substr(raw_input, saved_pos, *curr_pos - saved_pos);
	if (!token)
		exit(EXIT_FAILURE);
	if (has_dquotes_open || has_squotes_open)
		(*curr_pos)++;
	return (token);
}
