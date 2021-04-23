/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/23 12:22:35 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd_table	*get_cmd_table(void)
{
	t_cmd_table	*cmd_table;
	t_list		*new_cmd;
	int			raw_input_len;
	int			curr_pos;

	cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	if (!cmd_table)
		exit(EXIT_FAILURE);
	cmd_table->raw_input = get_raw_input();
	if (!is_input_valid(cmd_table->raw_input))
		return (cmd_table);
	curr_pos = 0;
	raw_input_len = ft_strlen(cmd_table->raw_input);
	while (curr_pos < raw_input_len)
	{
		new_cmd = ft_lstnew((void *)get_cmd(cmd_table->raw_input, &curr_pos));
		if (!new_cmd)
			exit(EXIT_FAILURE);
		ft_lstadd_front(&cmd_table->cmds, new_cmd);
		cmd_table->nb_cmds++;
	}
	return (cmd_table);
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
			continue ;
		else if (raw_input[i] == ' ' || raw_input[i] == ';'
				|| raw_input[i] == '|')
			break ;
		i++;
	}
	token = ft_substr(raw_input, *curr_pos, i);
	if (!token)
		exit(EXIT_FAILURE);
	*curr_pos = i;
	return (token);
}
