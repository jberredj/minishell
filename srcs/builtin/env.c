/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:42:14 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/25 20:39:10 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/ft_io.h"
#include "structs/t_env.h"
#include "error_codes.h"

int	env(char **argv, t_env *env)
{
	int	i;

	(void)argv;
	i = 0;
	while (env->envp[i])
	{
		ft_putendl_fd(env->envp[i], 1);
		i++;
	}
	return (SUCCESS);
}
