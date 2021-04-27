/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 10:38:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/04/27 18:43:03 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	write_prompt(void)
{
	int	ret;

	ret = write(STDOUT_FILENO, "$ ", 2);
	(void)ret;
}

void	write_gen_err_message(char *err_message)
{
	ft_putstr("minishell: ");
	ft_putstr(err_message);
	ft_putstr("\n");
}

void	init_minishell(t_msh *msh)
{
	ft_bzero(msh, sizeof(msh));
	if (!isatty(STDIN_FILENO))
		ft_exit(msh, EXIT_FAILURE);
	if (tcgetattr(STDIN_FILENO, &msh->old_term) == -1)
		ft_exit(msh, EXIT_FAILURE);
}

void	ft_exit(t_msh *msh, int exit_code)
{
	if (exit_code == EXIT_FAILURE)
	{
		if (errno != ENOTTY)
			tcsetattr(STDIN_FILENO, TCSANOW, &msh->old_term);
		ft_putstr(strerror(errno));
	}
	else if (exit_code == EXIT_SUCCESS)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &msh->old_term);
	}
	free_msh(msh);
	exit(exit_code);
}

void	free_msh(t_msh *msh)
{
	(void)msh;
}
