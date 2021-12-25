/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:23:30 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 20:40:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	unset(char **argv, t_env *env)
{
	int	i;
	int	argc;

	argc = 0;
	i = 1;
	while (argv[argc])
		argc++;
	while (i < argc)
	{
		env->error_in_builtin = pop_env_var_from_env(env, argv[i]);
		if (env->error_in_builtin)
			return (env->error_in_builtin);
		i++;
	}
	return (0);
}
