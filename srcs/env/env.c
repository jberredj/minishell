/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:42:34 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 11:56:31 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"
#include "env.h"

int	_update_envp_str(t_env_var *env_var_node)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(env_var_node->name, "=");
	if (!tmp)
		return (-1); //  CHANGE THIS TO PROPER MALLOC ERROR CODE
	ft_gnljoin(&tmp, env_var_node->value);
	if (!tmp)
		return (-1); // CF AU DESSUS
	free(env_var_node->envp_str);
	env_var_node->envp_str = tmp;
	return (0);
}
