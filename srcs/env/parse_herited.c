/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_herited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:41:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/29 21:36:51 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/includes/ft_to.h"
#include "error_codes.h"
#include "env.h"

int	check_path(t_env *env)
{
	if (!env->path)
		if (create_exported_var(env, "PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"))
			return (ERR_MALLOC);
	return (SUCCESS);
}

int	check_pwd(t_env *env)
{
	int			error;
	char		*cwd;

	error = SUCCESS;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		write(2, "minishell : getcwd() failed: No such file or directory\n", 55);
		cwd = ft_strdup(".");
		if (!cwd)
			return (ERR_MALLOC);
	}
	if (!env->pwd)
		error = create_exported_var(env, "PWD", cwd);
	else
		if (ft_strncmp(cwd, ".", 1) != 0)
			error = update_env_var_value(env->pwd, cwd);
	free(cwd);
	return (error);
}

int	check_shlvl(t_env *env)
{
	t_env_var	*shlvl;
	int			value;
	char		*new_val;
	int			error;

	error = 0;
	shlvl = find_env_var_in_lst(env->env_vars, "SHLVL");
	if (!shlvl)
		error = create_exported_var(env, "SHLVL", "1");
	else
	{
		value = ft_atoi(shlvl->value);
		value++;
		new_val = ft_itoa(value);
		if (!new_val)
			return (ERR_MALLOC);
		error = update_envp_var_value(shlvl, env->envp, new_val);
		free(new_val);
	}
	return (error);
}

int	parse_herited_envp(t_env *env, char **envp)
{
	size_t		nbr_var;
	int			i;

	nbr_var = 0;
	while (envp[nbr_var])
		nbr_var++;
	env->nbr_vars = nbr_var;
	i = -1;
	while (++i < (int)nbr_var)
	{
		if (create_exported_var_from_str(env, envp[i]))
		{
			ft_idllst_clear(&env->env_vars->list, free_env_var);
			env->env_vars = NULL;
			return (ERR_MALLOC);
		}
	}
	if (check_path(env))
		return (ERR_MALLOC);
	else if (check_pwd(env))
		return (ERR_MALLOC);
	else if (check_shlvl(env))
		return (ERR_MALLOC);
	return (0);
}
