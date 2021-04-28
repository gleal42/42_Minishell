/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:55:52 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/28 18:35:37 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

/*
** Initiate termcaps settings to use terminal capabilites
** Line-by-line comments:
** @4-5		Protect against a "TERM" env varible being unset
** @5		Indicate to the termcap lib with type of terminal we are using.
**			It will save that info internally so that use its capabilities later
*/

void	init_termcaps(t_termcaps *termcaps)
{
	char	*term_type;
	int		ret;

	if (tcgetattr(STDIN_FILENO, &termcaps->old_term) == -1)
		ft_exit(EXIT_FAILURE);
	if (IS_UNIX)
	{
		termcaps->buffer = ft_calloc(2048, 1);
		if (!termcaps->buffer)
			ft_exit(EXIT_FAILURE);
	}
	term_type = ft_getenv("TERM");
	if (!term_type)
		ft_exit(EXIT_FAILURE);
	ret = tgetent(termcaps->buffer, term_type);
	if (ret <= 0)
		ft_exit(EXIT_FAILURE);
	else if (!has_capabilities(termcaps))
		ft_exit(EXIT_FAILURE);
}

int	has_capabilities(t_termcaps *termcaps)
{
	int	check;

	termcaps->cursor_motion = tgetstr("cm", &termcaps->buffer);
	if (!termcaps->cursor_motion)
		check = 0;
	else
		check = 1;
	return (check);
}

int	ft_putint(int c)
{
	return (write(1, &c, 1));
}

/*
** The terminal has canonical mode on by default, meaning that the read
** function will return only when you press Enter, not when we reach the number
** of bytes indicated. For working with termcaps, we need to turn it off
** Line-by-line comments:
** @3		We get the current terminal config to modify it and then set it
** @4-5		The values of c_lflag represent the local modes settings. To turn on
**			or off a setting, we use masks and bitwise manipulation:
**			- The complement operator (~) inverts all the bits
**			- The AND operator (&) compares 2 bits. Sets bit to 1 only if both
**			bits are equal to 1
**			So, to take this example, it flips all the bits of ICANON and then
**			compares with original setting, effectively setting the bits
**			relating to ICANON to 0 and leaving the others intact
** @4		Turn off canonical processing
** @5		Disable local echo so that pressing up/down arrow doesn't output
**			^[[A and ^[[B
** @6-7		Changing control characters settings:
** @6		Read returns every single byte
** @7		No timeout so process every input without delay
*/

void	turn_off_canonical_mode(t_termcaps *termcaps)
{
	ft_bzero(&termcaps->new_term, sizeof(struct termios));
	termcaps->new_term = termcaps->old_term;
	termcaps->new_term.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	termcaps->new_term.c_oflag &= ~(OPOST);
	termcaps->new_term.c_cflag |= (CS8);
	termcaps->new_term.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	termcaps->new_term.c_cc[VMIN] = 0;
	termcaps->new_term.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termcaps->new_term) == -1)
		ft_exit(EXIT_FAILURE);
}

void	turn_on_canonical_mode(t_termcaps *termcaps)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termcaps->old_term) == -1)
		ft_exit(EXIT_FAILURE);
}
