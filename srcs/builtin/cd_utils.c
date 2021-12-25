/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:41:30 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/25 20:31:25 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../../libft/includes/ft_io.h"
#include "error_codes.h"
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
		fd = open(path, __O_DIRECTORY);
		if (fd == -1)
			return (FILE_ERROR | ISNOTDIR);
		close(fd);
		if (access(path, X_OK) != 0)
			return (FILE_ERROR | X_ERROR);
		return (SUCCESS);
	}
	return (FILE_ERROR | NOT_EXIST);
}

int	set_env_var(t_env *env, t_env_var *var, char *name, char *var_to_set)
{
	t_env_var	*tmp;

	if (!var)
	{
		tmp = create_env_var(name, var_to_set);
		if (!tmp)
		{
			env->error_in_builtin = ERR_MALLOC;
			return (ERR_MALLOC);
		}
		add_env_var(env, tmp);
		return (0);
	}
	return (2);
}

char	*get_cwd_err_protected(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_strdup("");
		if (!cwd)
			env->error_in_builtin = ERR_MALLOC;
	}
	return (cwd);
}

int	update_env(t_env *env, char *cwd)
{
	char		*old_pwd;
	int			error;

	old_pwd = get_cwd_err_protected(env);
	if (!old_pwd)
		return (ERR_MALLOC);
	if (chdir(cwd) != 0)
		return (FILE_ERROR | ISNOTDIR);
	else
	{
		if (set_pwd(env))
		{
			free(old_pwd);
			return (ERR_MALLOC);
		}
		error = set_env_var(env, env->old_pwd, "OLDPWD", old_pwd);
		if (error == 2)
			update_envp_var_value(env->old_pwd, env->envp, old_pwd);
		free(old_pwd);
		if (error == ERR_MALLOC)
			return (ERR_MALLOC);
	}	
	return (SUCCESS);
}
