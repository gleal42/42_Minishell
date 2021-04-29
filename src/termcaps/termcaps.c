/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:55:52 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/29 09:41:25 by dda-silv         ###   ########.fr       */
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

	termcaps->keys_on = tgetstr("ks", &termcaps->buffer);
	termcaps->left_arrow = tgetstr("kl", &termcaps->buffer);
	termcaps->right_arrow = tgetstr("kr", &termcaps->buffer);
	termcaps->up_arrow = tgetstr("ku", &termcaps->buffer);
	termcaps->down_arrow = tgetstr("kd", &termcaps->buffer);
	termcaps->save_cursor = tgetstr("sc", &termcaps->buffer);
	termcaps->restore_cursor = tgetstr("rc", &termcaps->buffer);
	termcaps->clear_end_line = tgetstr("ce", &termcaps->buffer);
	if (!termcaps->keys_on || !termcaps->left_arrow || !termcaps->right_arrow
		|| !termcaps->up_arrow || !termcaps->down_arrow)
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
** @param:	- [t_termcaps *] struct with all variables to set termcaps
** Line-by-line comments:
** @1		We get the current terminal config to modify it and then set it
** @2-3		The values of c_lflag represent the local modes settings. To turn on
**			or off a setting, we use masks and bitwise manipulation:
**			- The complement operator (~) inverts all the bits
**			- The AND operator (&) compares 2 bits. Sets bit to 1 only if both
**			bits are equal to 1
**			So, to take this example, it flips all the bits of ICANON and then
**			compares with original setting, effectively setting the bits
**			relating to ICANON to 0 and leaving the others intact
** @2		Turn off canonical processing
** @3		Disable local echo so that pressing up/down arrow doesn't output
**			^[[A and ^[[B
** @4-5		Changing control characters settings:
** @4		Read returns every single byte
** @5		No timeout so process every input without delay
** @6		Set the terminal on non-canonical mode (aka raw mode)
*/

void	turn_off_canonical_mode(t_termcaps *termcaps)
{
	termcaps->new_term = termcaps->old_term;
	termcaps->new_term.c_lflag &= ~ICANON;
	termcaps->new_term.c_lflag &= ~ECHO;
	termcaps->new_term.c_cc[VMIN] = 1;
	termcaps->new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termcaps->new_term) == -1)
		ft_exit(EXIT_FAILURE);
}

/*
** Turns on canonical mode. If function is called it means the canonical mode
** was off so we need to set it back on
** @param:	- [t_termcaps *] struct with all variables to set termcaps
** Line-by-line comments:
** @1		The old terminal settings already had canonical mode on so we just
**			need to go back to old settings
*/


void	turn_on_canonical_mode(t_termcaps *termcaps)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termcaps->old_term) == -1)
		ft_exit(EXIT_FAILURE);
}
