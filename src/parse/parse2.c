/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:58:53 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/24 21:07:23 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_list	*get_redirs(const char *raw_input, int *curr_pos)
{
	t_list	*lst_redirs;
	t_list	*redir;

	lst_redirs = 0;
	while (raw_input[*curr_pos] && raw_input[*curr_pos] != ';'
		&& raw_input[*curr_pos] != '|' && raw_input[*curr_pos] != '&')
	{
		redir = ft_lstnew((void *)get_redir(raw_input, curr_pos));
		if (!redir)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&lst_redirs, redir);
		skip_spaces(raw_input, curr_pos);
	}
	return (lst_redirs);
}

t_redir	*get_redir(const char *raw_input, int *curr_pos)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		exit(EXIT_FAILURE);
	if (raw_input[*curr_pos] == '<')
		*redir->type = raw_input[(*curr_pos)++];
	else if (!ft_strncmp(&raw_input[*curr_pos], ">>", 2))
	{
		ft_strncpy(redir->type, (char *)&raw_input[*curr_pos], 2);
		*curr_pos += 2;
	}
	else
		*redir->type = raw_input[(*curr_pos)++];
	skip_spaces(raw_input, curr_pos);
	redir->direction = get_token(raw_input, curr_pos);
	redir->is_executable = is_executable(redir->direction);
	return (redir);
}
