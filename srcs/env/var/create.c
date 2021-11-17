/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 15:10:06 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "env.h"
#include "../libft/includes/libft.h"

t_env_var	*create_env_var(char *name, char *value)
{
	t_env_var	*env_var_node;

	env_var_node = (t_env_var *)ft_calloc(1, sizeof(t_env_var));
	if (!env_var_node)
		return (NULL);
	env_var_node->list = ft_idllst_init(&env_var_node->list, env_var_node);
	env_var_node->id = -1;
	update_env_var_name(env_var_node, name);
	update_env_var_value(env_var_node, value);
	return (env_var_node);
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
