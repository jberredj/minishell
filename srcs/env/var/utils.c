/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:39:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/01 11:27:47 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "env.h"
#include "../libft/includes/libft.h"

t_env_var	*find_env_var_in_lst(t_env_var *env_vars, char *name)
{
	if (!env_vars && !ft_idllst_is_init(&env_vars->list))
		return (NULL);
	env_vars = ft_idllst_content(ft_idllst_get_head(&env_vars->list));
	while (env_vars)
	{
		if (ft_strncmp(env_vars->name, name, ft_strlen(name)) == 0)
			return (env_vars);
		env_vars = ft_idllst_next_content(&env_vars->list);
	}
	return (NULL);
}

int	pop_env_var_from_env(t_env *env, char *name)
{
	t_env_var	*node_to_pop;

	node_to_pop = find_env_var_in_lst(env->env_vars, name);
	if (!node_to_pop)
		return (1);
	env->nbr_vars--;
	if (node_to_pop->flags & ENV_VAR_EXPORTED)
	{
		env->envp[node_to_pop->id] = NULL;
		remove_from_envp(&env->envp, &env->nbr_exported);
	}
	ft_idllst_pop(&node_to_pop->list, free_env_var);
	return (0);
}

void	check_special_var(t_env *env, t_env_var *env_var_node)
{
	if (ft_strncmp(env_var_node->name, "PATH", 4) == 0)
		env->path = env_var_node;
	if (ft_strncmp(env_var_node->name, "PWD", 3) == 0)
		env->pwd = env_var_node;
	if (ft_strncmp(env_var_node->name, "OLDPWD", 6) == 0)
		env->old_pwd = env_var_node;
	if (ft_strncmp(env_var_node->name, "HOME", 4) == 0)
		env->home = env_var_node;
}

int	add_env_var(t_env *env, t_env_var *env_var_node)
{
	if (!env->env_vars)
		env->env_vars = env_var_node;
	else
		ft_idllst_add_back(&env_var_node->list, &env->env_vars->list);
	env->nbr_vars++;
	check_special_var(env, env_var_node);
	return (0);
}
