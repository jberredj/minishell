/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/17 11:03:25 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "env.h"
#include "../libft/includes/libft.h"
#include "error_codes.h"

t_env_var	*create_env_var(char *name, char *value)
{
	t_env_var	*env_var_node;

	env_var_node = (t_env_var *)ft_calloc(1, sizeof(t_env_var));
	if (!env_var_node)
		return (NULL);
	env_var_node->list = ft_idllst_init(&env_var_node->list, env_var_node);
	env_var_node->id = -1;
	if (update_env_var_name(env_var_node, name))
		free_env_var(&env_var_node->list);
	else if (update_env_var_value(env_var_node, value))
		free_env_var(&env_var_node->list);
	else
		return (env_var_node);
	return (NULL);
}

t_env_var	*create_env_var_from_str(char *str)
{
	t_env_var	*env_var;
	size_t		equal_loc;
	char		*name;
	char		*value;

	value = ft_strchr(str, '=');
	if (!value && *(value + 1) && value != str)
		return (NULL);
	equal_loc = (size_t)((value - str));
	value++;
	name = ft_calloc(equal_loc + 1, sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, equal_loc + 1);
	env_var = create_env_var(name, value);
	free(name);
	return (env_var);
}

int	create_exported_var(t_env *env, char *name, char *value)
{
	t_env_var	*node;

	node = create_env_var(name, value);
	if (!node)
		return (ERR_MALLOC);
	if (!env_var_to_envp(&env->envp, node, &env->nbr_exported))
	{
		free_env_var(&node->list);
		return (ERR_MALLOC);
	}
	add_env_var(env, node);
	return (SUCCESS);
}

int	create_exported_var_from_str(t_env *env, char *str)
{
	t_env_var	*node;

	node = create_env_var_from_str(str);
	if (!node)
		return (ERR_MALLOC);
	if (!env_var_to_envp(&env->envp, node, &env->nbr_exported))
	{
		free_env_var(&node->list);
		return (ERR_MALLOC);
	}
	add_env_var(env, node);
	return (SUCCESS);
}
