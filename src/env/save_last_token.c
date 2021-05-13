/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_last_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:48:00 by gleal             #+#    #+#             */
/*   Updated: 2021/05/13 18:04:30 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	save_last_token(t_cmd_table *cmd_table)
{
	t_list	*cmds;
	t_list	*tokens;
	char	*exec_path;

	cmds = cmd_table->cmds;
	while (cmds->next != 0)
		cmds = cmds->next;
	tokens = ((t_cmd *)(cmds->data))->tokens;
	while (tokens->next != 0)
		tokens = tokens->next;
	exec_path = convert_to_path(((t_token *)(tokens->data))->str);
	update_environment_var("_", exec_path, g_msh.dup_envp);
	free(exec_path);
}

char	*convert_to_path(char *token)
{
	char	*token_path;
	if (has_relative_path(token))
	{
		token_path = ft_strdup(token);
		if (!token_path)
			quit_program(EXIT_FAILURE);
	}
	else
		token_path = get_absolute_path(token);
	return (token_path);
}