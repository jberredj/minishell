/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_herited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:41:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/07 16:07:43 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <unistd.h>
#include <stdio.h>

void	check_path(t_env *env)
{
	t_env_var	*node;

	if (!env->path)
	{
		node = create_env_var("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
		add_env_var(env, node);
		env_var_to_envp(&env->envp, node, &env->nbr_exported);
	}
}

void	check_pwd(t_env *env)
{
	t_env_var	*node;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	perror("toupt :");
	if (!cwd)
	{
		write(2, "minishell : getcwd() failed: No such file or directory\n", 55);
		cwd = ft_strdup(".");
	}
	if (!env->pwd)
	{
		node = create_env_var("PWD", cwd);
		add_env_var(env, node);
		env_var_to_envp(&env->envp, node, &env->nbr_exported);
	}
	else
		if (ft_strncmp(cwd, ".", 1) != 0)
			update_env_var_value(env->pwd, cwd);
	free(cwd);
}

int	parse_herited_envp(t_env *env, char **envp)
{
	size_t		nbr_var;
	t_env_var	*env_var_node;
	int			i;

	nbr_var = 0;
	while (envp[nbr_var])
		nbr_var++;
	env->nbr_vars = nbr_var;
	i = -1;
	while (++i < (int)nbr_var)
	{
		env_var_node = create_env_var_from_str(envp[i]);
		if (!env_var_node)
		{
			ft_idllst_clear(&env->env_vars->list, free_env_var);
		}
		add_env_var(env, env_var_node);
		env_var_to_envp(&env->envp, env_var_node, &env->nbr_exported);
	}
	check_path(env);
	check_pwd(env);
	return (0);
}
