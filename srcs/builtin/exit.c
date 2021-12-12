/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:08:17 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/07 10:37:13 by jberredj         ###   ########.fr       */
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
		exit_code = ERROR_INVALID_VAL;
	}
	else
		exit_code = ERROR_TOO_MANY;
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
	return (exit_code | EXIT);
}
