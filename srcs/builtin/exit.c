/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:08:17 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 17:23:13 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include <stdint.h>
#include "error_codes.h"

static bool	check_num_valid(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}

int	print_exit_error(int error, char *precision)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (error == INVALID_VAL)
	{
		ft_putstr_fd(precision, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (2);
	}
	if (error == TOO_MANY)
	{
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	return (0);
}

static int	treat_exit(int ac, char **argv, t_env *env)
{
	int	num_valid;
	int	exit_code;

	num_valid = check_num_valid(argv[1]);
	if (num_valid && ac == 2)
	{
		exit_code = (uint8_t)ft_atoi(argv[1]);
		env->running = false;
	}
	else if (!num_valid)
	{
		env->running = false;
		exit_code = print_exit_error(INVALID_VAL, argv[1]);
	}
	else
		exit_code = print_exit_error(TOO_MANY, NULL);
	return (exit_code);
}

int	minish_exit(char **argv, t_env *env)
{
	int		ac;
	int		exit_code;

	ac = 0;
	while (argv[ac])
		ac++;
	if (ac == 1)
	{
		env->running = false;
		exit_code = env->exit_code;
	}
	else
		exit_code = treat_exit(ac, argv, env);
	return (exit_code);
}
