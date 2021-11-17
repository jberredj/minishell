/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:21:19 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 15:58:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "../libft/includes/libft.h"

char	*update_envp_str(t_env_var *env_var_node)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(env_var_node->name, "=");
	if (!tmp)
		return (NULL);
	ft_gnljoin(&tmp, env_var_node->value);
	if (!tmp)
		return (NULL);
	free(env_var_node->envp_str);
	env_var_node->envp_str = tmp;
	return (tmp);
}
