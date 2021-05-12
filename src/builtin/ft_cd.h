/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 08:58:24 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/12 08:58:52 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CD_H
# define FT_CD_H

# include "main.h"

int		ft_cd(t_list *tokens, t_list **env);
int		change_dir_home(char	*cur_pwd, t_list **env);
int		change_to_old_dir(char	*cur_pwd, t_list **env);

#endif
