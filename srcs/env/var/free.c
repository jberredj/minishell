/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:47:43 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/05 22:20:34 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_idllst.h"
#include "error_codes.h"
#include "structs/t_env.h"
#include "env.h"

void	free_env_var(void *elem)
{
	t_env_var	*env_var;

	env_var = ft_idllst_content(elem);
	if (env_var)
	{
		if (env_var->name)
			free(env_var->name);
		if (env_var->value)
			free(env_var->value);
		if (env_var->envp_str)
			free(env_var->envp_str);
		free(env_var);
	}
}

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
	if (node_to_pop->flags == ENV_VAR_EXPORTED)
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
