/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:58:53 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 12:25:42 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
** Gets redirections, which is a list of single redirections. One direction is
** something like ">> file1.txt". And each simple commands can have one or more
** redirections
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the raw_input  
** @return:	[t_list *] linked list with all the redirections in reading order
** Line-by-line comments:
** @5-6		Here ';', '|' and '&' delimite both simple commands and cmd_tables
*/

t_list	*get_redirs(const char *raw_input, int *curr_pos)
{
	t_list	*lst_redirs;
	t_list	*redir;

	lst_redirs = 0;
	while (raw_input[*curr_pos] && raw_input[*curr_pos] != ';'
		&& raw_input[*curr_pos] != '|' && raw_input[*curr_pos] != '&')
	{
		redir = ft_lstnew((void *)get_single_redir(raw_input, curr_pos));
		if (!redir)
			ft_exit(EXIT_FAILURE);
		ft_lstadd_back(&lst_redirs, redir);
		skip_spaces(raw_input, curr_pos);
	}
	return (lst_redirs);
}

/*
** Gets a single redirection
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the raw_input  
** @return:	[t_redir *] struct with a string with the direction and the type
** Line-by-line comments:
** @6-14	Gets the type
** @13-14	If it's not '<' nor ">>" then it must be '>'
*/

t_redir	*get_single_redir(const char *raw_input, int *curr_pos)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		ft_exit(EXIT_FAILURE);
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
	return (redir);
}
