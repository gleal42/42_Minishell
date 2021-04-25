/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:35:47 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/25 14:58:39 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_history.h"

void	set_termcaps(t_dlist **cmd_history)
{
	char	*term_name;
	char	*buffer;
	int		ret;
	int		width;

	buffer = 0;
	term_name = getenv("TERM");
	printf("Term_name: \"%s\"\n", term_name);
	
	ret = tgetent(buffer, term_name);
	printf("Ret: \"%d\"\n", ret);
	width = tgetflag("le");
	printf("Width: \"%d\"\n", width);

	(void)cmd_history;
}
