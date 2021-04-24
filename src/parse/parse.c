/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 10:59:21 by dda-silv         ###   ########.fr       */
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
		ft_lstadd_front(&ast->cmd_tables, cmd_table);
		ast->nb_cmd_tables++;
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
		ft_lstadd_front(&cmd_table->cmds, cmd);
		cmd_table->nb_cmds++;
	}
	return (cmd_table);
}

t_cmd	*get_cmd(const char *raw_input, int *curr_pos)
{
	t_cmd	*cmd;
	int		i;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		exit(EXIT_FAILURE);
	cmd->tokens = ft_calloc(1, sizeof(char *));
	if (!cmd->tokens)
		exit(EXIT_FAILURE);
	i = 0;
	while (ft_isspace(raw_input[*curr_pos]))
		(*curr_pos)++;
	while (raw_input[*curr_pos])
	{
		cmd->tokens = ft_realloc(cmd->tokens,
								(i + 1) * sizeof(char *),
								(i + 2) * sizeof(char *));
		if (!cmd->tokens)
			exit(EXIT_FAILURE);
		cmd->tokens[i++] = get_token(raw_input, curr_pos);
		while (ft_isspace(raw_input[*curr_pos]))
			(*curr_pos)++;
		if (raw_input[*curr_pos] == ';' || raw_input[*curr_pos] == '|')
		{
			cmd->delimiter = raw_input[(*curr_pos)++];
			break ;
		}
	}
	cmd->tokens[i] = 0;
	cmd->nb_tokens = i;
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
