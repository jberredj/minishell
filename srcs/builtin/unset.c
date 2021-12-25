/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:23:30 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 17:43:33 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/ft_io.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
#include "env.h"
#include "builtin.h"

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
