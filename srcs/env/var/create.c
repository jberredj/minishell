/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:38:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/10 10:48:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "env.h"
#include "../libft/includes/ft_string.h"

t_env_var	*create_env_var(char *name, char *value, int id)
{
	t_env_var	*elem;

	elem = (t_env_var *)ft_calloc(1, sizeof(t_env_var));
	if (!elem)
		return (NULL);
	elem->id = id;
	update_env_var_name(elem, name);
	update_env_var_value(elem, value);
	return (elem);
}

t_env_var	*create_env_var_from_str(char *str, int id)
{
	t_env_var	*elem;
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
	elem = create_env_var(name, value, id);
	free(name);
	return (elem);
}
