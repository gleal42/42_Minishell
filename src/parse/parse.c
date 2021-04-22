/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/22 21:26:58 by dda-silv         ###   ########.fr       */
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
	if (has_quotes_open(cmd_table->raw_input))
	{
		write_gen_err_message("syntax error (open quotes)");
		return (cmd_table);
	}
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

/*
** Checks if the input has any open quotes (single or double).
** Considered as open quotes:
** - "
** - " '
** - " ' " '
** Not considered as open quotes:
** - " "
** - " ' "
** - " ' ' "
** @param:	- [char *] the unchanged line entered in stdin
** @return:	[int] true or false
** Line-by-line comments:
** @10-11	If we find a double quotes and single quotes are not open,
**			we set has_double_quotes_open to its opposite, meaning:
**			- true if it was initially false (we are opening double quotes)
**			- false if it was initially true (we are closing double quotes)
**			We don't care about double quotes if single quotes are open because
**			it will all be part of the token enclosed by the single quotes
** @12-13	Exact same logic as for the double quotes
*/

int	has_quotes_open(const char *raw_input)
{
	int	check;
	int	has_double_quotes_open;
	int	has_single_quotes_open;

	check = 1;
	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (*raw_input)
	{
		if (*raw_input == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (*raw_input == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		raw_input++;
	}
	if (has_double_quotes_open || has_single_quotes_open)
		check = 1;
	else
		check = 0;
	return (check);
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
	while (raw_input[*curr_pos])
	{
		cmd->tokens = ft_realloc(cmd->tokens,
								(i + 1) * sizeof(char *),
								(i + 2) * sizeof(char *));
		if (!cmd->tokens)
			exit(EXIT_FAILURE);
		while (ft_isspace(raw_input[*curr_pos]))
			(*curr_pos)++;
		cmd->tokens[i++] = get_token(raw_input, curr_pos);
		if (raw_input[*curr_pos - 1] == ';' || raw_input[*curr_pos - 1] == '|')
		{
			cmd->split = raw_input[*curr_pos - 1];
			break ;
		}
	}
	cmd->tokens[i + 1] = 0;
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
	token = ft_substr(raw_input, *curr_pos, i - 1);
	if (!token)
		exit(EXIT_FAILURE);
	*curr_pos = i;
	return (token);
}
