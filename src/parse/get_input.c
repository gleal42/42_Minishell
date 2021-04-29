/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:23:20 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/30 00:20:17 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_input.h"

/*
** Gets the characters entered in the command line by user. Multiline commands
** aren't supported so we only call get_next_line once
** @return:	[char *] line entered without any alterations nor checks
*/

char	*get_input(t_dlist *input_history, t_termcaps *termcaps)
{
	char	*input;
	char	buf[BUFSIZ];
	int		i;
	int		nb_char_read;

	i = 0;
	ft_bzero(buf, BUFSIZ);
	while (!ft_strchr(buf, '\n'))
	{
		nb_char_read = read(STDIN_FILENO, &buf[i], BUFSIZ - i);
		if (is_up_down_arrow(&buf[i], termcaps))
			parse_input_history(&input_history, termcaps, buf, &i);
		else if (!ft_strcmp(&buf[i], termcaps->backspace))
			delete_single_char(termcaps, buf, &i);
		else if (nb_char_read > 1)
			ft_bzero(&buf[i], BUFSIZ - i);
		else
			i += write(STDOUT_FILENO, &buf[i], 1);
	}
	buf[i - 1] = '\0';
	input = ft_strdup(buf);
	if (!input)
		ft_exit(EXIT_FAILURE);
	return (input);
}

int	is_up_down_arrow(char *buf, t_termcaps *termcaps)
{
	int	check;

	if (!ft_strcmp(termcaps->up_arrow, buf))
		check = 1;
	else if (!ft_strcmp(termcaps->down_arrow, buf))
		check = 1;
	else
		check = 0;
	return (check);
}

void	parse_input_history(t_dlist **input_history,
							t_termcaps *termcaps,
							char *buf,
							int *i)
{
	char	*input;

	if (!has_history(*input_history, termcaps, buf, i))
		return ;
	input = (*input_history)->data;
	if (!ft_strcmp(termcaps->up_arrow, &buf[*i])
			&& (*input_history)->next)
		*input_history = (*input_history)->next;
	else if (!ft_strcmp(termcaps->down_arrow, &buf[*i])
			&& (*input_history)->prev)
	{
		*input_history = (*input_history)->prev;
		input = (*input_history)->data;
	}
	tputs(termcaps->del_line, 1, ft_putint);
	write_prompt();
	ft_bzero(buf, BUFSIZ);
	ft_strcpy(buf, input);
	*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
}

int	has_history(t_dlist *input_history,
				t_termcaps *termcaps,
				char *buf,
				int *i)
{
	int	check;

	if (!input_history)
		check = 0;
	else if (input_history && !ft_strcmp(termcaps->down_arrow, &buf[*i])
			&& !input_history->prev)
		check = 0;
	else if (input_history)
		check = 1;
	else if (!ft_strcmp(termcaps->up_arrow, &buf[*i])
			&& !input_history->next)
		check = 0;
	else if (!ft_strcmp(termcaps->down_arrow, &buf[*i])
			&& !input_history->prev)
		check = 0;
	else
		check = 1;
	if (!check)
		ft_bzero(&buf[*i], BUFSIZ - *i);
	return (check);
}

void	delete_single_char(t_termcaps *termcaps, char *buf, int *i)
{
	int	len;

	ft_bzero(&buf[*i], BUFSIZ - *i);
	len = ft_strlen(buf);
	if (len == 0)
		return ;
	tputs(termcaps->del_line, 1, ft_putint);
	write_prompt();
	buf[len - 1] = '\0';
	*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
}
