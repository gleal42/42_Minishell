/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:01:55 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 10:02:08 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Splits a single token into several different fields. For example, the token:
** "$TERM"'$PATH'hello1"hel'lo2"'hel"lo3'
** would be split in 5 nodes. Each node keeps its original quotes
** "$TERM"
** '$PATH'
** hello1
** "hel'lo2"
** 'hel"lo3'
** @param:	- [char *] token to split
** @return:	[t_list *] linked list with all pieces of token
** Line-by-line comments:
** @12		Save beginning of token piece
** @13-16	Parse until end of token piece
** @17-23	Extract string, create a new node and add to back of existing ones
*/

t_list	*get_split_token(char *token)
{
	t_list	*split_token;
	t_list	*new_node;
	char	*token_piece;
	int		curr_pos;
	int		saved_pos;

	split_token = 0;
	curr_pos = 0;
	saved_pos = 0;
	while (token[curr_pos])
	{
		saved_pos = curr_pos;
		if (is_quote(token[curr_pos]))
			skip_quotes((const char *)token, &curr_pos);
		else
			skip_letters((const char *)token, &curr_pos);
		token_piece = ft_substr(token, saved_pos, curr_pos - saved_pos);
		if (!token_piece)
			quit_program(EXIT_FAILURE);
		new_node = ft_lstnew((void *)token_piece);
		if (!new_node)
			quit_program(EXIT_FAILURE);
		ft_lstadd_back(&split_token, new_node);
	}
	return (split_token);
}

/*
** Joins all strings of a linked lists into a BIG string
** @param:	- [t_list *] split token to join
** @return:	[char *] new string result of all the pieces of token
** Line-by-line comments:
** @4		Gets the cumulated size of the linked list
** @8-12	Parse split tokens and concat them all
*/

char	*join_split_token(t_list *split_token)
{
	char	*token;
	int		new_token_size;

	new_token_size = get_new_token_size(split_token);
	token = ft_calloc(new_token_size + 1, sizeof(char));
	if (!token)
		quit_program(EXIT_FAILURE);
	while (split_token)
	{
		ft_strcat(token, (char *)split_token->data);
		split_token = split_token->next;
	}
	ft_lstclear(&split_token, free);
	return (token);
}

/*
** Gets cumulated size of the linked list
** @param:	- [t_list *] split token to join
** @return:	[int] sum of the size of all strings in the linked list
*/

int	get_new_token_size(t_list *split_token)
{
	int		size;
	char	*token;

	size = 0;
	while (split_token)
	{
		token = split_token->data;
		size += ft_strlen(token);
		split_token = split_token->next;
	}
	return (size);
}

/*
** Replaces an environment variable when only $ENV. We need to have an edge case
** for this because when $ENV is used without quotes spaces are not to be
** printed (I know, I know, one more edge case. Fear not, it won't be the
** last...)
** @param:	- [char **] token to replace
*/

void	replace_one_var(char **str)
{
	char	*env;
	char	*trimmed;

	env = ft_getenv(*str + 1);
	if (!env)
	{
		free(*str);
		*str = ft_strdup("");
		if (!*str)
			quit_program(EXIT_FAILURE);
		return ;
	}
	trimmed = ft_strtrim(env, " ");
	if (!trimmed)
		quit_program(EXIT_FAILURE);
	free(env);
	free(*str);
	*str = trimmed;
}
