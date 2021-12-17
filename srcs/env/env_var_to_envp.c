/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_to_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:10:53 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/17 10:38:26 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../libft/includes/libft.h"

int	add_new_envp(char ***envp, t_env_var *node, size_t *nbr_exported)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)ft_calloc(*nbr_exported + 2, sizeof(char *));
	if (!new_envp)
		return (-1);
	i = -1;
	if (*envp)
	{
		while ((*envp)[++i])
			new_envp[i] = (*envp)[i];
		free(*envp);
	}
	*envp = new_envp;
	*nbr_exported += 1;
	node->id = *nbr_exported - 1;
	new_envp[node->id] = node->envp_str;
	node->flags ^= ENV_VAR_EXPORTED;
	return (0);
}

int	update_existing_envp(char ***envp, t_env_var *env_var_node)
{
	(*envp)[env_var_node->id] = env_var_node->envp_str;
	return (0);
}

char	*env_var_to_envp(char ***envp, t_env_var *env_var_node,
	size_t *nbr_exported)
{
	if (!envp || !env_var_node || !ft_idllst_is_init(&env_var_node->list))
		return (NULL);
	if (!update_envp_str(env_var_node))
		return (NULL);
	if (!(env_var_node->flags & ENV_VAR_EXPORTED))
	{
		if (add_new_envp(envp, env_var_node, nbr_exported))
			return (NULL);
	}
	else
		update_existing_envp(envp, env_var_node);
	return (env_var_node->envp_str);
}
