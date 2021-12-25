/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:39:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 14:10:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "env.h"
#include "../libft/includes/libft.h"
#include "error_codes.h"

static void	check_special_pop(t_env *env, char *name)
{
	if (ft_strncmp(name, "PATH", 5) == 0)
		env->path = NULL;
	if (ft_strncmp(name, "PWD", 4) == 0)
		env->pwd = NULL;
	if (ft_strncmp(name, "OLDPWD", 7) == 0)
		env->old_pwd = NULL;
	if (ft_strncmp(name, "HOME", 5) == 0)
		env->home = NULL;
}

t_env_var	*find_env_var_in_lst(t_env_var *env_vars, char *name)
{
	if (!env_vars || !ft_idllst_is_init(&env_vars->list))
		return (NULL);
	env_vars = ft_idllst_content(ft_idllst_get_head(&env_vars->list));
	while (env_vars)
	{
		if (ft_strncmp(env_vars->name, name, ft_strlen(name) + 1) == 0)
			return (env_vars);
		env_vars = ft_idllst_next_content(&env_vars->list);
	}
	return (NULL);
}

void	update_envp_id(t_env_var *env_vars, int id)
{
	while (env_vars)
	{
		env_vars->id = id;
		env_vars = ft_idllst_next_content(&env_vars->list);
		id++;
	}
}

void	remove_from_env(t_env *env, t_env_var *node_to_pop)
{
	bool	first;
	bool	last;

	first = ft_idllst_is_head(&node_to_pop->list);
	last = true;
	if (ft_idllst_size(&node_to_pop->list) > 1)
		last = false;
	if (last)
		env->env_vars = NULL;
	else if (first)
		env->env_vars = ft_idllst_next_content(&node_to_pop->list);
	ft_idllst_pop(&node_to_pop->list, free_env_var);
}

int	pop_env_var_from_env(t_env *env, char *name)
{
	t_env_var	*node_to_pop;
	int			error;

	error = 0;
	node_to_pop = find_env_var_in_lst(env->env_vars, name);
	if (!node_to_pop)
		return (NOT_FOUND);
	env->nbr_vars--;
	if (node_to_pop->flags & ENV_VAR_EXPORTED)
	{
		env->envp[node_to_pop->id] = NULL;
		if (remove_from_envp(&env->envp, &env->nbr_exported))
			return (ERR_MALLOC);
		update_envp_id(ft_idllst_next_content(&node_to_pop->list),
			node_to_pop->id);
	}
	remove_from_env(env, node_to_pop);
	check_special_pop(env, name);
	return (SUCCESS);
}

void	check_special_var(t_env *env, t_env_var *env_var_node)
{
	if (ft_strncmp(env_var_node->name, "PATH", 5) == 0)
		env->path = env_var_node;
	if (ft_strncmp(env_var_node->name, "PWD", 4) == 0)
		env->pwd = env_var_node;
	if (ft_strncmp(env_var_node->name, "OLDPWD", 7) == 0)
		env->old_pwd = env_var_node;
	if (ft_strncmp(env_var_node->name, "HOME", 5) == 0)
		env->home = env_var_node;
}

void	add_env_var(t_env *env, t_env_var *env_var_node)
{
	if (!env->env_vars)
		env->env_vars = env_var_node;
	else
		ft_idllst_add_back(&env_var_node->list, &env->env_vars->list);
	env->nbr_vars++;
	check_special_var(env, env_var_node);
}
