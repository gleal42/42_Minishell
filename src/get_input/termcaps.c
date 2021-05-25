/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:55:52 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/17 12:16:18 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

/*
** Initiate termcaps settings to use terminal capabilites
** @param:	- [t_termcaps *] struct with terminal capabilities capabilities
** Line-by-line comments:
** @3-4		Get the terminal settings
** @5-7		Protect against a "TERM" env varible being unset
** @8-9		Indicate to the termcap lib with type of terminal we are using.
**			It will save that info internally to use its capabilities later
** @10-11	Checks if the terminal has all the capabilities required to run the
**			the program and sets them to the struct termcaps
*/

void	init_termcaps(t_termcaps *termcaps)
{
	char	*term_type;

	if (tcgetattr(STDIN_FILENO, &termcaps->old_term) == -1)
		quit_program(EXIT_FAILURE);
	term_type = ft_getenv("TERM");
	if (!term_type)
		quit_program(EXIT_FAILURE);
	if (tgetent(termcaps->buffer, term_type) <= 0)
		quit_program(EXIT_FAILURE);
	else if (!has_capabilities(termcaps))
		quit_program(EXIT_FAILURE);
	free(term_type);
}

/*
** Checks if the terminal has all the capabilities required to run the the
** program and sets them to the struct termcaps
** To store a capability we use tgetstr / tgetnum / tgetflag and to use a
** capabality we use tputs
** @param:	- [t_termcaps *] struct with terminal capabilities capabilities
** @return:	[int] true or false
** Line-by-line comments:
** @3-5		"ks" enables the terminal to return specific ANSI codes when special
**			keys are pressed like up_arrow
** @6		If "ks" is used, "ke" needs to be used at the end of the program
** @7-12	Function keys aren't like common capabilities. To use them we don't
**			have to call tputs. Instead, we need to compare the values read
**			by the buffer when pressing to up arrow to the return value of "ku"
** @9-12	For some reason GNU version of termcaps (used in MacOS) returns '\b'
**			so we need to manually set the value
** @13		Capability that allows to delete the content of the line where the
** 			cursor currently is positioned 
** @14		Capability that allows to delete the content of the line where the
** 			cursor currently is positioned 
*/

int	has_capabilities(t_termcaps *termcaps)
{
	int	check;

	termcaps->keys_on = tgetstr("ks", &termcaps->buffer);
	if (termcaps->keys_on)
		tputs(termcaps->keys_on, 1, ft_putint);
	termcaps->keys_off = tgetstr("ke", &termcaps->buffer);
	termcaps->up_arrow = tgetstr("ku", &termcaps->buffer);
	termcaps->down_arrow = tgetstr("kd", &termcaps->buffer);
	if (IS_LINUX)
		termcaps->backspace = tgetstr("kb", &termcaps->buffer);
	else
		termcaps->backspace = ft_strdup("\x7f");
	termcaps->del_line = tgetstr("dl", &termcaps->buffer);
	termcaps->set_cursor_begin = tgetstr("cr", &termcaps->buffer);
	if (!termcaps->keys_on || !termcaps->keys_off
		|| !termcaps->up_arrow || !termcaps->down_arrow
		|| !termcaps->backspace || !termcaps->del_line
		|| !termcaps->set_cursor_begin)
		check = 0;
	else
		check = 1;
	return (check);
}

/*
** The terminal has canonical mode on by default, meaning that the read
** function will return only when you press Enter, not when we reach the number
** of bytes indicated. For working with termcaps, we need to turn it off
** @param:	- [t_termcaps *] struct with all variables to set termcaps
** Line-by-line comments:
** @1		We get the current terminal config to modify it and then set it
** @2-5		The values of c_lflag represent the local modes settings. To turn on
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
** @4		Turn off SIGINT (Ctrl-C) and SIGTSTP (Ctrl-Z) signals
** @5		Disable Ctrl-V
** @6		Modify input flag: disable Ctrl-S and Ctrl-Q
** @7-8		Changing control characters settings:
** @7		Read returns every single byte
** @8		No timeout so process every input without delay
** @9		Set the terminal on non-canonical mode (aka raw mode)
*/

void	turn_off_canonical_mode(t_termcaps *termcaps)
{
	termcaps->new_term = termcaps->old_term;
	termcaps->new_term.c_lflag &= ~ICANON;
	termcaps->new_term.c_lflag &= ~ECHO;
	termcaps->new_term.c_lflag &= ~ISIG;
	termcaps->new_term.c_lflag &= ~IEXTEN;
	termcaps->new_term.c_iflag &= ~IXON;
	termcaps->new_term.c_cc[VMIN] = 1;
	termcaps->new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termcaps->new_term) == -1)
		quit_program(EXIT_FAILURE);
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
		quit_program(EXIT_FAILURE);
}

/*
** Function that gets called by tputs
** @param:	- [int] character to write
** @return:	[int] number of characters written
*/

int	ft_putint(int c)
{
	return (write(1, &c, 1));
}
