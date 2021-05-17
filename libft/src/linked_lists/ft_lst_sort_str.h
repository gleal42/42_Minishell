/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort_str.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:52:06 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/17 17:45:06 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_SORT_STR_H
# define FT_LST_SORT_STR_H

# include "libft.h"

static void		split_list(t_list *head,
					t_list **first_half,
					t_list **second_half);
static t_list	*merge_sort(t_list *a, t_list *b, int (*op)(char *, char *));

#endif
