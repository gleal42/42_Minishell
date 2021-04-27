/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:35:47 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/27 19:04:31 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_history.h"

// void	set_termcaps(t_dlist *cmd_history)
// {
// 	t_termcaps	*tc;

// 	tc = ft_calloc(1, sizeof(t_termcaps));
// 	if (!tc)
// 		exit(EXIT_FAILURE);
// 	turn_off_canonical_processing();
// 	init_termcaps(tc);
// 	parse_cmd_history(cmd_history, tc);
// 	free_termcaps(tc);
// }

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

// void	turn_off_canonical_processing(void)
// {
// 	struct termios	term_config;

// 	tcgetattr(STDIN_FILENO, &term_config);
// 	term_config.c_lflag &= ~ICANON;
// 	// term_config.c_lflag &= ~ECHO;
// 	term_config.c_cc[VMIN] = 1;
// 	term_config.c_cc[VTIME] = 0;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term_config);
// }

/*
** Initiate termcaps settings to use terminal capabilites
** Line-by-line comments:
** @4-5		Protect against a "TERM" env varible being unset
** @5		Indicate to the termcap lib with type of terminal we are using.
**			It will save that info internally so that use its capabilities later
*/

// void	init_termcaps(t_termcaps *tc)
// {
// 	char	*term_type;
// 	char	*tmp;

// 	term_type = getenv("TERM");
// 	if (!term_type)
// 		exit(EXIT_FAILURE);
// 	tgetent(NULL, term_type);
// 	tmp = tgetstr("pc", NULL);
// 	if (tmp)
// 		PC = *tmp;
// 	else
// 		PC = 0;
// 	BC = tgetstr("le", NULL);
// 	UP = tgetstr("up", NULL);
// 	tc->cursor_motion = tgetstr("cm", NULL);
// 	tc->clear_curr_line = tgetstr("cd", NULL);
// 	tc->clear_end_line = tgetstr("ce", NULL);
// 	tc->save_cursor = tgetstr("sc", NULL);
// 	tc->restore_cursor = tgetstr("rc", NULL);
// 	tc->resolution = tgetnum("li") * tgetnum("co");
// 	if (!tc->cursor_motion || !tc->clear_curr_line || !tc->clear_end_line
// 		|| !tc->save_cursor || !tc->restore_cursor || tc->resolution < 0)
// 		exit(EXIT_FAILURE);
// }

// void	free_termcaps(t_termcaps *tc)
// {
// 	// free(tc->cursor_motion);
// 	// free(tc->clear_curr_line);
// 	// free(tc->clear_end_line);
// 	// free(tc->save_cursor);
// 	// free(tc->restore_cursor);
// 	free(tc);
// }

// void	parse_cmd_history(t_dlist *cmd_history, t_termcaps *tc)
// {
// 	// tputs(tc->save_cursor, 1, ft_putint);
// 	// tputs(tgoto(tc->cursor_motion, 5, 5), 1, ft_putint);
// 	// sleep(5);
// 	// tputs(tc->restore_cursor, 1, ft_putint);

// 	(void)cmd_history;
// 	(void)tc;
// }
