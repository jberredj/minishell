/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:02 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 11:55:41 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"

int	update_env_var_value(t_env_var *env_var_node, char *value)
{
	char	*tmp;

	tmp = ft_strdup(value);
	if (!tmp)
		return (-1); // CHANGE THIS TO PROPER MALLOC ERROR CODE
	if (env_var_node->value)
		free(env_var_node->value);
	env_var_node->value = tmp;
	return (0);
}

int	update_env_var_name(t_env_var *env_var_node, char *name)
{
	char	*tmp;

	tmp = ft_strdup(name);
	if (!tmp)
		return (-1); // CHANGE THIS TO PROPER MALLOC ERROR CODE
	if (env_var_node->name)
		free(env_var_node->name);
	env_var_node->name = tmp;
	return (0);
}
