/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dds <dda-silv@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 10:26:41 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 13:58:06 by dds              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

/*
** Skips all spaces starting at curr_pos while incrementing *curr_pos
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the raw_input  
*/

void	skip_spaces(const char *raw_input, int *curr_pos)
{
	while (ft_isspace(raw_input[*curr_pos]))
		(*curr_pos)++;
}

/*
** Converts a linked list to a NULL-terminated array of strings
** @param:	- [t_list *] list with string as data
**			- [type] param_value
** @return:	[char **] NULL-terminated array of strings
** Line-by-line comments:
** @12&15	We don't want to free the strings within each node of the list
**			because we'll keep their address in strs. The ft_lstdel_int does
**			nothing to the data within each node
*/

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
** Checks if the char is a cmd delimiter
** @param:	- [char] the characters
** @return:	[int] true or false
** Line-by-line comments:
** @9-10	& isn't supposed to be a delimiter. But "&&" is. If '&' is on its
**			own, the function is_input_valid() will flag that
*/

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

/*
** Sets the values of has_dquotes_open and has_squotes_open depending on the
** value of raw_input[*curr_pos]
** @param:	- [const char *] the unchanged line entered in stdin
**			- [int *] the current parsing position within the raw_input  
**			- [int *] reference to the uninitialised var has_dquotes_open
**			- [int *] reference to the uninitialised var has_squotes_open
** @return:	[type] return_value
** Line-by-line comments:
** @9		We need to increment once if we found quotes
*/

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
