/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:02:10 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/29 00:32:42 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../../libft/includes/ft_io.h"
#include "structs/t_env.h"
#include "error_codes.h"
#include "builtin.h"

int	print_error(int error, char *path)
{
	if (error)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (error == HOME_ERROR)
			ft_putendl_fd("HOME not set", 2);
		if (error & (NOT_EXIST | ISNOTDIR | X_ERROR))
			perror(path);
		return (1);
	}
	return (0);
}

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
			return (print_error(HOME_ERROR, NULL));
		return (print_error(update_env(env, home->value), home->value));
	}
	error = check_access(argv[1]);
	if (error)
		return (print_error(error, argv[1]));
	pwd = argv[1];
	return (print_error(update_env(env, pwd), pwd));
}
