/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:02 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/06 11:48:13 by ddiakova         ###   ########.fr       */
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

	update_env_var_value(env_var_node, value);
	if (env_var_node->flags & ENV_VAR_EXPORTED)
	{
		tmp = update_envp_str(env_var_node);
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
