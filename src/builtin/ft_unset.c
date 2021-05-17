/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:42:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/17 11:47:30 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_unset.h"

/*
** Deletes environment variable from Envp list
** @param:	- [t_list *] arguments following unset
**			- [t_list **] pointer to envp linked list
** @return:	[int] exit status
** Line-by-line comments:
** @6		Checking for invalid input and writing error message
** @10-11	First checking if environment variable exists and deleting it in
**			case it does
*/

int	ft_unset(t_list *tokens, t_list **env)
{
	char	*token_str;

	while (tokens)
	{
		token_str = tokens->data;
		if (!has_valid_identifier_unset(token_str))
			return (EXIT_FAILURE);
		if (has_only_one_cmd())
		{	
			if (is_env_var(token_str, *env))
				delete_env_var(token_str, env);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

/*
** Goes through the environment variable list and deletes one of the nodes if
** it finds the match (always making sure that the list is connected)
** @param:	- [char *] potential environment variable to be deleted
**			- [t_list **] pointer to envp linked list
** Line-by-line comments:
** @16		Function that uses the node number of a linked list to delete that
**			node
*/

void	delete_env_var(char *var, t_list **env)
{
	t_list	*env_ptr;
	int		i;
	char	*cur_env;
	int		env_index;

	env_ptr = *env;
	env_index = 0;
	while (env_ptr)
	{
		i = 0;
		cur_env = (char *)(env_ptr->data);
		while (var[i] && cur_env[i] && (var[i] == cur_env[i]))
			i++;
		if (!var[i] && (cur_env[i] == '=' || cur_env[i] == '\0' ))
		{
			ft_lstdel_node_nbr(env, env_index, ft_delete_list_str);
			return ;
		}
		env_index++;
		env_ptr = env_ptr->next;
	}
}

/*
** Frees the data in the pointer and sets the pointer to null
** @param:	- [void *] list->data
*/

void	ft_delete_list_str(void *data)
{
	free(data);
	data = 0;
}
