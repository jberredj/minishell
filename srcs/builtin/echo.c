/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:02:31 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/25 20:33:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "../../libft/includes/libft.h"

static void	echo_print(int i, int argc, char **argv)
{
	while (argv[++i])
	{
		ft_putstr_fd(argv[i], 1);
		if (i != argc - 1)
			write(1, " ", 1);
	}
}

int	echo(char **argv, t_env *env)
{
	bool	n_param;
	int		argc;
	int		i;

	(void)env;
	argc = 1;
	while (argv[argc])
		argc++;
	n_param = false;
	i = 0;
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "-n", 2) == 0)
		{
			i++;
			n_param = true;
		}
	}
	echo_print(i, argc, argv);
	if (!n_param)
		write(1, "\n", 1);
	return (0);
}
