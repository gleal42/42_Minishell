/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:37:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/22 19:03:51 by dda-silv         ###   ########.fr       */
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
	cmd_table->nb_cmds = 0;	
	curr_pos = 0;
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

int	has_quotes_open(char *raw_input)
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

t_cmd	*get_cmd(char *raw_input, int *curr_pos)
{
	t_cmd	*cmd;

	cmd = 0;
	return (cmd);
	(void)cmd;
	(void)raw_input;
	(void)curr_pos;
}

char	*get_token(char *raw_input, int *curr_pos)
{
	char	*token;

	token = 0;
	return (token);
	(void)raw_input;
	(void)curr_pos;
	(void)token;
}
