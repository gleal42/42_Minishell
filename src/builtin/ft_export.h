/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:06:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/14 10:40:59 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_H
# define FT_EXPORT_H

# include "main.h"

int		ft_export(t_list *tokens, t_list **env);
void	print_all_exported_vars(t_list *env);
void	update_env_var_with_token(char *token_str, char *var, t_list *env);
void	create_environment_var(char *token_str, t_list **env);

#endif
