/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:56:26 by gleal             #+#    #+#             */
/*   Updated: 2021/05/04 23:39:21by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		ft_unset(t_list *tokens, t_list **env)
{
	char	*token_str;

	(void)env;
	while (tokens)
	{
		token_str = ((t_token *)tokens->data)->str;
		if (!has_valid_identifier(token_str))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	has_valid_identifier(char *token_str)
{
	char	err_message[100];
	int		check;

	ft_bzero(err_message, 0);
	if (!is_token_valid_unset(token_str, err_message))
	{
		check = 0;
		errno = ENOEXEC;
		write_gen_err_message(err_message);
	}
	else
		check = 1;
	return (check);
}

int	is_token_valid_unset(char *token_str,char *err_message)
{
	int		check;

	if (ft_strchr(token_str, '=')
		|| ft_strchr(token_str, '\'')
		|| ft_strchr(token_str, '"'))
	{
		check = 0;
		ft_strcpy(err_message, "unset: `");
		ft_strcat(err_message, token_str);
		ft_strcat(err_message, "': not a valid identifier");
	}
	else
		check = 1;
	return (check);
}
//errno = EACCES;
//ft_putstr_fd(strerror(errno), 2);