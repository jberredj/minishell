/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_herited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:41:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 12:07:18 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	set_parsed_vars_in_env(t_env *env)
{
	t_env_var	*env_var_node;

	env_var_node = find_env_var_in_lst(env->env_vars, "PATH");
	env->path = env_var_node;
	env_var_node = find_env_var_in_lst(env->env_vars, "PWD");
	env->pwd = env_var_node;
	env_var_node = find_env_var_in_lst(env->env_vars, "OLDPWD");
	env->old_pwd = env_var_node;
	env_var_node = find_env_var_in_lst(env->env_vars, "HOME");
	env->home = env_var_node;
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
		env_var_node = create_env_var_from_str(envp[i], i);
		if (!env_var_node)
		{
			ft_idllst_clear(&env->env_vars->list, free_env_var);
		}
		add_env_var(env, env_var_node);
	}
	set_parsed_vars_in_env(env);
	return (0);
}
