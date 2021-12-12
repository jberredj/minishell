/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:23:30 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/12 17:45:26 by ddiakova         ###   ########.fr       */
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
		pop_env_var_from_env(env, argv[i]);
		i++;
	}
	return (0);
}
