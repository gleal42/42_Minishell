/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:01:55 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/16 22:21:23 by dda-silv         ###   ########.fr       */
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
		if (token[curr_pos] == '"' || token[curr_pos] == '\'')
			skip_quotes((const char *)token, &curr_pos);
		else
		{
			while (token[curr_pos]
				&& token[curr_pos] != '"' && token[curr_pos] != '\'')
				curr_pos++;
		}
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

