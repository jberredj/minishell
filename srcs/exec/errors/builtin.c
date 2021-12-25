/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:54:08 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 20:50:02 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_io.h"
#include "structs/t_command.h"
#include "structs/t_env.h"
#include "error_codes.h"
#include "builtin.h"

char	*builtin_pointer_to_name(int (*builtin)(char**, t_env *))
{
	if (builtin == echo)
		return ("echo: ");
	else if (builtin == cd)
		return ("cd: ");
	else if (builtin == pwd)
		return ("pwd: ");
	else if (builtin == export)
		return ("export: ");
	else if (builtin == unset)
		return ("unset: ");
	else if (builtin == env)
		return ("env: ");
	else if (builtin == minish_exit)
		return ("exit: ");
	return ("unknown builtin: ");
}

int	panic_builtin_out(int error, t_command *command)
{
	command->exit_code = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin_pointer_to_name(command->builtin), 2);
	ft_putstr_fd("fatal error: ", 2);
	if (error == (CREATE_ERROR | 1))
		ft_putendl_fd("sigaction() failed", 2);
	if (error == (CREATE_ERROR | 2))
		ft_putendl_fd("fork() failed", 2);
	if (error == ERR_MALLOC)
		ft_putendl_fd("malloc() failed", 2);
	return (1);
}
