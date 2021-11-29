/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:02:31 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/29 22:27:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "../../libft/includes/ft_string.h"

int	echo(char **argv, char **envp)
{
	bool	n_param;
	int		argc;
	int		i;

	(void)envp;
	argc = 0;
	while (argv[argc])
		argc++;
	n_param = false;
	if (argc > 0)
		if (ft_strncmp(argv[0], "-n", 2))
			n_param = true;
	i = -1;
	while (argv[++i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (i != argc - 1)
			write(1, " ", 1);
	}
	if (n_param)
		write(1, "\n", 1);
	return (0);
}
