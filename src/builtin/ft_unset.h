/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:07:11 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 09:07:39 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UNSET_H
# define FT_UNSET_H

# include "main.h"

int		ft_unset(t_list *tokens, t_list **env);
void	delete_env_var(char *var, t_list **env);
void	ft_delete_list_str(void *data);

#endif
