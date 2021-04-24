/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 20:55:20 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
	return (ast);
}

/*
** Gets the characters entered in the command line by user. Multiline commands
** aren't supported so we only call get_next_line once
** @return:	[char *] Line entered without any alterations nor checks
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

char	*get_token(const char *raw_input, int *curr_pos)
{
	char	*token;
	int		has_dquotes_open;
	int		has_squotes_open;
	int		i;

	set_quotes(raw_input, curr_pos, &has_dquotes_open, &has_squotes_open);
	i = *curr_pos;
	while (raw_input[i])
	{
		if ((raw_input[i] == '"' && has_dquotes_open)
			|| (raw_input[i] == '\'' && has_squotes_open))
			break ;
		else if ((has_dquotes_open || has_squotes_open) && i++)
			continue ;
		else if (is_delimiter(raw_input[i]))
			break ;
		i++;
	}
	token = ft_substr(raw_input, *curr_pos, i - *curr_pos);
	if (!token)
		exit(EXIT_FAILURE);
	if (has_dquotes_open || has_squotes_open)
		i++;
	*curr_pos = i;
	return (token);
}
