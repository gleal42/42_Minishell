/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_all.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:49:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/02 18:44:06 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTRIM_ALL_H
# define FT_STRTRIM_ALL_H

# include "libft.h"

static size_t	get_length(char **strs);
static void		concat_all(char *dest, char **strs);

#endif
