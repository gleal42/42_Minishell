/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:23:20 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 10:51:06 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_input.h"

/*
** Gets the characters entered in the command line by user. We need to handle
** specific cases:
** - Up / down keypresses to check history
** - Backspace keypresses to delete a character
** Multiline commands aren't supported.
** @param:	- [t_dlist *] double linked list with previous input as nodes. 
**						  As we only pass the pointer its order nor the amount
**						  of nodes is changed by get_input()
**			- [t_termcaps *] struct with terminal capabilities capabilities
** @return:	[char *] line entered without any alterations nor checks
** Line-by-line comments:
** @7		We initialize our buf where we are temporarely storing the input
**			from user. The size of BUFSIZ is 8192 (defined in stdio.h)
**			If the input is larger than 8192... embrace the SEGFAULT life
** @10		Important piece of code so let's split it: 
**			- "nb_char_read": having set canonical mode off means read() returns
**			after each keypress regardless of the buffer_size argument. But that
**			doesn't mean we are always reading one byte at a time. For the
**			letter 'A', only 1 char will be read but the up arrow taking 3 bytes
**			in ANSI code, nb_char_read will have a value of 3
**			- "&buf[i]": we set the new character read after all previous
**			buffer. The i index is updated in parse_input_history(), in
**			delete_single_char() and by write().
**			- "BUFSIZ - i": size left in our buffer
** @13-14	We compare the values just read to the ANSI value of the backspace
**			that we received from the termcaps lib.
**			Here we need to keep in mind that the buffer has been previously set
**			to NULL so the new value set in the buffer are NULL-terminated
** @15-16	If the number of characters read is above 2 bytes and it's not
**			up / down arrow or backspace, it means it's a special character that
**			should not be writting on the stdout like Home. Yet it's in our
**			buffer so we need to set to NULL starting where that special
**			characters was stored
**			Because of bit encoding (I think), extended ASCII characters
**			(e.g. é, @) take 2 bytes instead of 1
**			Ctrl + <letter> may cause unexpected behaviours, is_ctrl() makes
**			the only ctrl combinaision's allowed are ctrl - c and ctrl - d
** @17-18	When user presses ctrl-c, End of Text (ASCII code 3) is sent to
**			buffer. The expected behaviour is to write "^C" to stdout and reset
**			the command line
** @19-20	When user presses ctrl-d, End of Transmission (ASCII code 4) is sent
**			to the buffer. The expected behaviour is to write "exit" and to exit
**			the shell
** @21-22	We know that only one character has been read so we can safely write
**			it to STDOUT while incrementing i so that next character is read
**			after the one just written
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
		else if (nb_char_read > 2 || (nb_char_read == 1 && is_ctrl(buf[i])))
			ft_bzero(&buf[i], BUFSIZ - i);
		else if (buf[i] == CTRL_C)
			reset_cmd_line(buf, &i, &input_history);
		else if (buf[i] == CTRL_D)
			exit_program(buf, i);
		else
			i += write(STDOUT_FILENO, &buf[i], nb_char_read);
	}
	input = extract_input(buf, i);
	return (input);
}

/*
** Checks if the characters in buffer are up or down arrow
** @param:	- [char *] buffer reprenting one or more characters
**			- [t_termcaps *] struct with terminal capabilities capabilities
** @return:	[int] true or false
*/

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

/*
** Parse the input history, set the buffer to the value of the history and
** update the index based on the length of that value
** @param:	- [t_dlist **] double linked list with an input previously entered
**                         as node. We pass the pointer to pointer because
**                         we need the change to be permanent for get_input.
**						   This allows the function to effectively parse it.
**						   Otherwise, we would only have access to the previous
**						   input.
**			- [t_termcaps *] struct with terminal capabilities capabilities
**			- [char *] buffer where the history input will be set
**			- [int *] index where are in the buffer
** Line-by-line comments:
** @3-7		There is not necessarely history to show so we delete the arrow
**			input from buffer and we return
** @8-9		Case: up arrow + only node in the list
** @10-14	Case: up arrow + more than one node in list
** @15-19	Case: down arrow + more than one node in list
** @20		Delete the current line from STDOUT
** @21		Set cursor at the beginning of current line
** @25		While we are writting the new input, we change the value of *i
**			so that the next char input while be set after the input just wrote
*/

void	parse_input_history(t_dlist **input_history,
							t_termcaps *termcaps,
							char *buf,
							int *i)
{
	char	*input;

	if (!has_history(*input_history, termcaps, &buf[*i]))
	{
		ft_bzero(&buf[*i], BUFSIZ - *i);
		return ;
	}
	if (!ft_strcmp(termcaps->up_arrow, &buf[*i]) && !(*input_history)->next)
		input = (*input_history)->data;
	else if (!ft_strcmp(termcaps->up_arrow, &buf[*i]))
	{
		input = (*input_history)->data;
		*input_history = (*input_history)->next;
	}
	else if (!ft_strcmp(termcaps->down_arrow, &buf[*i]))
	{
		*input_history = (*input_history)->prev;
		input = (*input_history)->data;
	}
	tputs(termcaps->del_line, 1, ft_putint);
	tputs(termcaps->set_cursor_begin, 1, ft_putint);
	write_prompt();
	ft_bzero(buf, BUFSIZ);
	ft_strcpy(buf, input);
	*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
}

/*
** Checks if, according to the keypressed, there is a history to show
** @param:	- [t_dlist *] double linked list with an input previously entered
**        				  as node
**			- [t_termcaps *] struct with terminal capabilities capabilities
**			- [char *] buffer where the user input is set
** @return:	[int] true or false
** Line-by-line comments:
** @5-6		If we press down arrow, we need to make sure that we are not at the
**			beginning of the list
*/

int	has_history(t_dlist *input_history, t_termcaps *termcaps, char *buf)
{
	int	check;

	if (!input_history)
		check = 0;
	else if (!ft_strcmp(termcaps->down_arrow, buf) && !input_history->prev)
		check = 0;
	else
		check = 1;
	return (check);
}

/*
** Deletes the last characters inputed
** @params	- [t_termcaps *] struct with terminal capabilities capabilities
**			- [char *] buffer where the history input will be set
**			- [int *] index where are in the buffer
** Line-by-line comments:
** @3-7		We are deleting both the last char input and the backspace ANSI code
** 			Extended ASCII characters take 2 bytes
** @8		Delete the current line from STDOUT
** @9		Set cursor at the beginning of current line
*/

void	delete_single_char(t_termcaps *termcaps, char *buf, int *i)
{
	int	nb_char_to_delete;

	if (*i == 0 || ft_isascii(buf[*i - 1]))
		nb_char_to_delete = 1;
	else
		nb_char_to_delete = 2;
	ft_bzero(&buf[*i - nb_char_to_delete], BUFSIZ - *i + nb_char_to_delete);
	tputs(termcaps->del_line, 1, ft_putint);
	tputs(termcaps->set_cursor_begin, 1, ft_putint);
	write_prompt();
	*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
}
