/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:41:30 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/06 17:19:06 by jberredj         ###   ########.fr       */
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
			return (FILE_ERROR | ISNOTDIR_ERROR);
		close (fd);
		if (access(path, X_OK) != 0)
			return (FILE_ERROR | X_ERROR);
		return (SUCCESS);
	}
	return (FILE_ERROR | NOT_EXIST_ERROR);
}

int	set_env_var(t_env *env, t_env_var *var, char *name, char *var_to_set)
{
	t_env_var	*tmp;

	if (!var)
	{
		tmp = create_env_var(name, var_to_set);
		add_env_var(env, tmp);
		return (0);
	}
	return (1);
}

int	update_env(t_env *env, char *cwd)
{
	char		*old_pwd;
	char		*pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(cwd) != 0)
		return (FILE_ERROR | ISNOTDIR_ERROR);
	else
	{
		pwd = getcwd(NULL, 0);
		if ((set_env_var(env, env->pwd, "PWD", pwd) != 0))
			update_envp_var_value(env->pwd, env->envp, pwd);
		free (pwd);
		if ((set_env_var(env, env->old_pwd, "OLDPWD", old_pwd) != 0))
			update_envp_var_value(env->old_pwd, env->envp, old_pwd);
		free (old_pwd);
	}	
	return (SUCCESS);
}
