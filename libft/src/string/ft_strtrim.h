/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 21:43:18 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/08 12:05:02 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTRIM_H
# define FT_STRTRIM_H

# include "libft.h"

static size_t	get_length(char const *s1, char const *set);
static void		trim(char *new_str,
					size_t size_new_str,
					char const *s1,
					char const *set);

#endif
