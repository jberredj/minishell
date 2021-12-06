/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:42:14 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/06 18:06:27 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/ft_io.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
#include "env.h"
#include "builtin.h"

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
