/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:02:10 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/06 16:20:01 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "../../libft/includes/ft_io.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
#include <stdio.h>
#include "env.h"
#include "builtin.h"

int	cd(char **argv, t_env *env)
{	
	t_env_var	*home;
	int			argc;
	int			error;
	char		*pwd;

	home = NULL;
	argc = check_args(argv);
	if (argc == -1)
		return (1);
	if (argc == 1)
	{
		home = env->home;
		if (!home)
			return (HOME_ERROR);
		chdir(home->value);
		return (update_env(env, home->value) | CD_ERROR);
	}
	error = check_access(argv[1]);
	if (error)
		return (print_error(error, argv[1]) | CD_ERROR);
	pwd = argv[1];
	return (update_env(env, pwd) | CD_ERROR);
}
