/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:26:41 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 17:10:41 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

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

void	print_ast(t_ast *ast)
{
	t_list	*cmd_table;

	printf("print_ast:\n");
	printf("raw_input: \"%s\"\n", ast->raw_input);
	printf("nb_cmd_tables: %d\n", ast->nb_cmd_tables);
	cmd_table = ast->cmd_tables;
	while (cmd_table)
	{
		print_cmd_table(cmd_table->data);
		cmd_table = cmd_table->next;
		printf("\n");
	}
}

void	print_cmd_table(t_cmd_table *cmd_table)
{
	t_list	*cmd;

	printf("\n");
	printf("print_cmd_table:\n");
	printf("nb_cmds: %d\n", cmd_table->nb_cmds);
	printf("delimiter: \"%s\"\n", cmd_table->delimiter);
	cmd = cmd_table->cmds;
	while (cmd)
	{
		print_cmd(cmd->data);
		cmd = cmd->next;
		printf("\n");
	}
}

void	print_cmd(t_cmd *cmd)
{
	int		i;

	printf("\n");
	printf("print_cmd\n");
	printf("nb_tokens: %d\n", cmd->nb_tokens);
	i = 0;
	while (i <= cmd->nb_tokens)
	{
		printf("Tokens[%d]: \"%s\"\n", i, cmd->tokens[i]);
		i++;
	}
}
