/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:47:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 11:24:23 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "../libft/includes/ft_idllst.h"

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
		free(env_var);
	}
}
