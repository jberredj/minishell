/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:11:56 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/12 19:38:55 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs/t_env.h>
#include <structs/t_command.h>
#include "error_codes.h"
#include "../libft/includes/libft.h"
#include <stdio.h>

int	exit_error(int error, char *desc)
{
	int	code;

	code = (error & 0xFF);
	error &= ~0xFF;
	error &= (EXIT_ERROR);
	if (error)
	{
		ft_putstr_fd("exit: ", 2);
		if (error & ERROR_INVALID_VAL)
		{
			code = 2;
			ft_putstr_fd(desc, 2);
			ft_putendl_fd(": numeric argument required", 2);
		}
		if (error & ERROR_TOO_MANY)
		{
			code = 1;
			ft_putendl_fd("too many arguments", 2);
		}
	}
	return (code);
}

void	print_minishell(int error)
{
	if ((error & BUILTIN_ERROR & ~0xFF))
		ft_putstr_fd("minishell: ", 2);
}

int	builtin_errors(int error, char *desc)
{
	if (error)
	{
		print_minishell(error);
		if (error & EXIT)
			return (exit_error(error ^ EXIT, desc));
	}
	return (0);
}

int	minishell_error(int error, char *desc)
{
	if (error)
	{
		if (error & BUILTIN)
			return (builtin_errors(error, desc));
	}
	return (0);
}
