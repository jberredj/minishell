/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:08:17 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/01 15:24:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include <stdint.h>

bool	check_num_valid(char *str)
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

int	minish_exit(char **argv, t_env *env)
{
	int		ac;
	bool	num_valid;
	int		exit_code;

	ac = 0;
	while (argv[ac])
		ac++;
	if (ac == 1)
		env->running = false;
	num_valid = check_num_valid(argv[1]);
	if (num_valid && ac == 2)
	{
		exit_code = (uint8_t)ft_atoi(argv[1]);
		env->running = false;
	}
	else if (!num_valid)
	{
		ft_putstr_fd("minishell : exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		env->running = false;
		exit_code = 2;
	}
	else
	{
		exit_code = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	return (exit_code);
}
