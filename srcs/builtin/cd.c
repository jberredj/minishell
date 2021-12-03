/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:02:10 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/03 17:21:51 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "../../libft/includes/ft_io.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
#include <stdio.h>

int	check_args(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (-1);
	}
	return (argc);
}

int	check_access(char *path)
{
	int	fd;

	if (access(path, F_OK) == 0)
	{
		fd = open(path, O_DIRECTORY);
		if (fd == -1)
			return (FILE_ERROR | ISDIR_ERROR);
		close (fd);
		if (access(path, X_OK) != 0)
			return (FILE_ERROR | X_ERROR);
		return (SUCCESS);
	}
	return (FILE_ERROR | NOT_EXIST_ERROR);
}

int	print_error(int error, char *path)
{
	// ecrire erreur 
	return (1);
}

// int update_env
// {
// getcwd
// 	return (ERROR)
// }

int	cd(char **argv, t_env *env)
{	
	t_env_var	*pwd;
	int			argc;
	int			error;
	char		*cwd;

	argc = check_args(argv);
	if (argc == -1)
		return (1);
	if (argc == 1)
		return (0); // cd home a gerer
	error = check_access(argv[1]);
	if (error)
		return (print_error(error, argv[1]));
	// cwd = getcwd(NULL, 0);
	// if (!cwd)
	// {
		
	// }
	// set var d'environement - static char OLDPWD
	if (chdir(argv[1]))
		printf ("chdir");
	return (0);
}

// cd tout court => si HOME est set (chdir HOME - update env var) ou pas (ERROR)
// update PWD et OLDPWD
