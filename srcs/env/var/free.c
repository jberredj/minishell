/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:47:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/09 15:37:10 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"

void	free_env_var(void *elem)
{
	t_env_var	*env_elem;

	env_elem = (t_env_var *)elem;
	if (env_elem)
	{
		if (env_elem->name)
			free(env_elem->name);
		if (env_elem->value)
			free(env_elem->value);
		free(env_elem);
	}
}
