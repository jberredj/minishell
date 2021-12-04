/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:02:10 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/04 22:19:11 by ddiakova         ###   ########.fr       */
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
	if (error == HOME_ERROR)
		ft_putstr_fd("cd : HOME not set\n", 2);
	if (error == FILE_ERROR | ISDIR_ERROR)
	{
		ft_putstr_fd("cd : ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	if (error == FILE_ERROR | X_ERROR)
	{
		ft_putstr_fd("cd : ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	return (1);
}

int update_env(t_env *env, char *cwd)
{
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(cwd) != 0)
		return (FILE_ERROR | ISDIR_ERROR);
	else
	{
		env->pwd->value = cwd;
		env->old_pwd->value = old_pwd;
	}	
 	return (0);
}

int	cd(char **argv, t_env *env)
{	
	t_env_var	*cwd;
	int			argc;
	int			error;
	char		*pwd;
	//static char	old_pwd_copy[BUFFER_SIZE + 1];

	cwd = NULL;
	argc = check_args(argv);
	if (argc == -1)
		return (1);
	if (argc == 1)
	{
		cwd = find_env_var_in_lst(env->env_vars, "HOME");
		if (!cwd)
			return (HOME_ERROR);
		return (update_env(env, cwd->value));
	}
	error = check_access(argv[1]);
	if (error)
		return (print_error(error, argv[1]));
	//*old_pwd_copy = *getcwd(NULL, 0);
	// printf ("%s\n", old_pwd_copy);
	pwd = argv[1];
		return (update_env(env,pwd));
	return (0);
}

// cd tout court => si HOME est set (chdir HOME - update env var) ou pas (ERROR)
// update PWD et OLDPWD
