/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:02 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/05 22:20:47 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "error_codes.h"
#include "env.h"

int	update_env_var_value(t_env_var *env_var_node, char *value)
{
	char	*tmp;

	tmp = ft_strdup(value);
	if (!tmp)
		return (ERR_MALLOC);
	if (env_var_node->value)
		free(env_var_node->value);
	env_var_node->value = tmp;
	return (0);
}

int	update_envp_var_value(t_env_var *env_var_node, char **envp, char *value)
{
	char	*tmp;

	if (update_env_var_value(env_var_node, value))
		return (ERR_MALLOC);
	if (env_var_node->flags == ENV_VAR_EXPORTED)
	{
		tmp = update_envp_str(env_var_node);
		if (!tmp)
			return (ERR_MALLOC);
		envp[env_var_node->id] = tmp;
	}
	return (0);
}

int	update_env_var_name(t_env_var *env_var_node, char *name)
{
	char	*tmp;

	tmp = ft_strdup(name);
	if (!tmp)
		return (ERR_MALLOC);
	if (env_var_node->name)
		free(env_var_node->name);
	env_var_node->name = tmp;
	return (0);
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
