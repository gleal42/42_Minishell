/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:35:47 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/26 19:04:11 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_history.h"

void	set_termcaps(t_dlist *cmd_history)
{
	t_termcaps	*termcaps;

	termcaps = ft_calloc(1, sizeof(t_termcaps));
	if (!termcaps)
		exit(EXIT_FAILURE);
	turn_off_canonical_processing();
	init_termcaps(termcaps);
	parse_cmd_history(cmd_history, termcaps);
}

/*
** The terminal has canonical processing on by default, meaning that the read
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

void	turn_off_canonical_processing(void)
{
	struct termios	term_config;

	tcgetattr(STDIN_FILENO, &term_config);
	term_config.c_lflag &= ~ICANON;
	term_config.c_lflag &= ~ECHO;
	term_config.c_cc[VMIN] = 1;
	term_config.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_config);
}

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

	term_type = getenv("TERM");
	if (!term_type)
		exit(EXIT_FAILURE);
	tgetent(NULL, term_type);
	termcaps->cursor_motion = tgetstr("cm", NULL);
	termcaps->clear_curr_line = tgetstr("cd", NULL);
	termcaps->clear_end_line = tgetstr("ce", NULL);
	termcaps->save_cursor = tgetstr("sc", NULL);
	termcaps->resolution = tgetnum("li") * tgetnum("co");
}

void	parse_cmd_history(t_dlist *cmd_history, t_termcaps *termcaps)
{
	int c;
	int	col;
	int	row;

	while (read(0, &c, sizeof(c)) > 0)
	{
		get_cursor_position(&col, &row, termcaps);
		// printf("Col: \"%d\"\n", col);
		// printf("Row: \"%d\"\n", row);
		if (c == UP_ARROW)
		{
			// delete previously writen chars
			// write prev command
		}
		else if (c == DOWN_ARROW)
		{
			// delete previously writen chars
			// write next command
		}
		else
		{
			col++;
			write(STDIN_FILENO, &c, 1);
		}
       	c = 0; // flush buffer
	}
	(void)cmd_history;
	(void)termcaps;
}
