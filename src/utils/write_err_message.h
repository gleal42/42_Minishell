/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_err_message.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:31:09 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/25 11:33:32 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITE_ERR_MESSAGE_H
# define WRITE_ERR_MESSAGE_H

# include "main.h"

void	write_msh_error(char *err_message);
void	write_exec_error(char *exec_name, char *err_message);
void	write_msh_exec_error(char *exec_name, char *err_message);
void	write_msh_exec_arg_error(char *exec_name, char *arg, char *err_message);
void	write_msh_exec_arg_error_nocolon(char *exec_name,
			char *arg,
			char *err_message);

#endif
