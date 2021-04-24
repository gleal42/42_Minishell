/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:26:41 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 21:06:48 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

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

int	is_delimiter(char c)
{
	int	check;

	if (c == ' ')
		check = 1;
	else if (c == ';')
		check = 1;
	else if (c == '|')
		check = 1;
	else if (c == '&')
		check = 1;
	else if (c == '<')
		check = 1;
	else if (c == '>')
		check = 1;
	else
		check = 0;
	return (check);
}

int	is_executable(char *str)
{
	int	check;

	check = 1;
	return (check);
	(void)str;
}

void	set_quotes(const char *raw_input,
					int *curr_pos,
					int *has_dquotes_open,
					int *has_squotes_open)
{
	*has_dquotes_open = 0;
	*has_squotes_open = 0;
	if (raw_input[*curr_pos] == '"' || raw_input[*curr_pos] == '\'')
	{
		if (raw_input[*curr_pos] == '"')
			*has_dquotes_open = 1;
		else if (raw_input[*curr_pos] == '\'')
			*has_squotes_open = 1;
		(*curr_pos)++;
	}
}

/*
** Functions below will be deleted when project is finished
*/

void	print_ast(t_ast *ast)
{
	t_list	*cmd_table;

	printf("print_ast:\n");
	printf("raw_input: \"%s\"\n", ast->raw_input);
	printf("nb_cmd_tables: %d\n", ft_lstsize(ast->cmd_tables));
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
	printf("nb_cmds: %d\n", ft_lstsize(cmd_table->cmds));
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
	t_list	*tmp;

	printf("\n");
	printf("print_cmd\n");
	i = 0;
	while (cmd->tokens[i])
	{
		printf("Tokens[%d]: \"%s\"\n", i, cmd->tokens[i]);
		i++;
	}
	tmp = cmd->redirs;
	printf("nb_redirs: %d\n", ft_lstsize(cmd->redirs));
	while (tmp)
	{
		print_redir(tmp->data);
		tmp = tmp->next;
		printf("\n");
	}
}

void	print_redir(t_redir *redir)
{
	printf("direction: \"%s\"\n", redir->direction);
	printf("type: \"%s\"\n", redir->type);
	printf("is_executable: %d\n", redir->is_executable);
}
