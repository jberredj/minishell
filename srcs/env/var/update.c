/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:02 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/09 15:37:06 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"

int	update_env_var_value(t_env_var *elem, char *value)
{
	char	*tmp;

	tmp = ft_strdup(value);
	if (!tmp)
		return (-1); // CHANGE THIS TO PROPER MALLOC ERROR CODE
	if (elem->value)
		free(elem->value);
	elem->value = tmp;
	return (0);
}

int	update_env_var_name(t_env_var *elem, char *name)
{
	char	*tmp;

	tmp = ft_strdup(name);
	if (!tmp)
		return (-1); // CHANGE THIS TO PROPER MALLOC ERROR CODE
	if (elem->name)
		free(elem->name);
	elem->name = tmp;
	return (0);
}
