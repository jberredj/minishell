/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:42:34 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/10 10:27:06 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"
#include "env.h"

int	_update_envp_str(t_env_var *elem)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(elem->name, "=");
	if (!tmp)
		return (-1); //  CHANGE THIS TO PROPER MALLOC ERROR CODE
	ft_gnljoin(&tmp, elem->value);
	if (!tmp)
		return (-1); // CF AU DESSUS
	free(elem->envp_str);
	elem->envp_str = tmp;
	return (0);
}
