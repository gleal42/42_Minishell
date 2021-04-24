/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:26:41 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 17:50:25 by dda-silv         ###   ########.fr       */
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

void	skip_spaces(const char *raw_input, int *curr_pos)
{
	while (ft_isspace(raw_input[*curr_pos]))
		(*curr_pos)++;
}

char	**convert_list_to_arr(t_list **lst)
{
	t_list	*tmp;
	char	**strs;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(*lst);
	strs = ft_calloc(len + 1, sizeof(char *));
	tmp = *lst;
	while (i < len)
	{
		strs[i++] = (char *)tmp->data;
		tmp = tmp->next;
	}
	ft_lstclear(lst, ft_lstdel_int);
	return (strs);
}

/*
** Functions below will be deleted when project is finished
*/

void	print_ast(t_ast *ast)
{
	t_list	*cmd_table;

	printf("print_ast:\n");
	printf("raw_input: \"%s\"\n", ast->raw_input);
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
	i = 0;
	while (cmd->tokens[i])
	{
		printf("Tokens[%d]: \"%s\"\n", i, cmd->tokens[i]);
		i++;
	}
}
