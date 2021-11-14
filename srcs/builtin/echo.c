/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:23:55 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/14 20:46:32 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../libft/includes/ft_string.h"

int	echo(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		write(1, " ", 1);
		write (1, "\n", 2);
	}
	else
	{	
		i = 1;
		while (argv[i])
		{
			write(1, &argv[i], ft_strlen(argv[i]));
			write(1, " ", 1);
			i++;
		}
		write (1, "\n", 2);
	}
	return (0);
}
