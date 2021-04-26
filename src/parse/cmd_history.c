/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:35:47 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/26 16:24:02 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_history.h"

void	set_termcaps(t_dlist **cmd_history)
{
	char	*buffer;

	buffer = 0;
	init_termcaps(cmd_history, &buffer);
	turn_off_canonical_processing();

	output_cmd(((t_ast *)(*cmd_history)->data)->raw_input);
	tputs(tgetstr("ic", &buffer), 1, putchar);
	// int width = tgetnum("co");
	// printf("Width: \"%d\"\n", width);
	// int height = tgetnum("li");
	// printf("Height: \"%d\"\n", height);

	// char *cl_str = tgetstr("cd", &buffer);
	// ft_putstr(cl_str);
	// printf("Cl_str: \"%s\"\n", cl_str);
	// char *cm_str = tgetstr("cm", &buffer);
	// ft_putstr(cm_str);
	// printf("Cm_str: \"%s\"\n", cm_str);

	(void)cmd_history;
}

void	init_termcaps(t_dlist **cmd_history, char **buffer)
{
	char	*term_name;
	char	*tmp;

	term_name = getenv("TERM");
	if (!term_name)
		exit(EXIT_FAILURE);
	tgetent(*buffer, term_name);
	tmp = tgetstr("pc", buffer);
	if (tmp)
		PC = *tmp;
	else
		PC = 0;
	BC = tgetstr("le", buffer);
	UP = tgetstr("up", buffer);

	(void)cmd_history;
}

void	output_cmd(const char *raw_input)
{
	// printf("Raw_input: \"%s\"\n", raw_input);	
	// tputs(tgetstr("le", buffer), 1, pchr);
	(void)raw_input;
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
** @5		Disable local echo
** @6-7		Changing control characters settings:
** @6		Read returns every single byte
** @7		No timeout so process every input without delay
*/

void	turn_off_canonical_processing(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}