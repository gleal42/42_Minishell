/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:01:55 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/18 17:05:59 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

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

int	get_new_token_size(t_list *split_token)
{
	int	size;

	size = 0;
	while (split_token)
	{
		size += ft_strlen((const char *)split_token->data);
		split_token = split_token->next;
	}
	return (size);
}

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
