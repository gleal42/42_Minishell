/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 17:52:56 by dda-silv         ###   ########.fr       */
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
		if (raw_input[*curr_pos] == ';')
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
	while (raw_input[*curr_pos] && raw_input[*curr_pos] != ';')
	{
		token = ft_lstnew((void *)get_token(raw_input, curr_pos));
		if (!token)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&lst_tokens, token);
		skip_spaces(raw_input, curr_pos);
		if (raw_input[*curr_pos] == '|')
		{
			(*curr_pos)++;
			break ;
		}
	}
	cmd->tokens = convert_list_to_arr(&lst_tokens);
	return (cmd);
}

char	*get_token(const char *raw_input, int *curr_pos)
{
	char	*token;
	int		has_double_quotes_open;
	int		has_single_quotes_open;
	int		i;

	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	if (raw_input[*curr_pos] == '"' || raw_input[*curr_pos] == '\'')
	{
		if (raw_input[*curr_pos] == '"')
			has_double_quotes_open = 1;
		else if (raw_input[*curr_pos] == '\'')
			has_single_quotes_open = 1;
		(*curr_pos)++;
	}
	i = *curr_pos;
	while (raw_input[i])
	{
		if ((raw_input[i] == '"' && has_double_quotes_open) ||
				(raw_input[i] == '\'' && has_single_quotes_open))
			break ;
		else if (has_double_quotes_open || has_single_quotes_open)
		{
			i++;
			continue ;
		}
		else if (raw_input[i] == ' ' || raw_input[i] == ';'
				|| raw_input[i] == '|')
			break ;
		i++;
	}
	token = ft_substr(raw_input, *curr_pos, i - *curr_pos);
	if (!token)
		exit(EXIT_FAILURE);
	if (has_double_quotes_open || has_single_quotes_open)
		i++;
	*curr_pos = i;
	return (token);
}
