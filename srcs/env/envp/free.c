/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:43:16 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 17:06:14 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../libft/includes/ft_idllst.h"

int	remove_from_envp(char ***envp, t_env_var *env_var_node,
	size_t *nbr_exported)
{
	char	**tofree;
	char	**new_envp;
	int		i;

	new_envp = (char **)ft_calloc(*nbr_exported, sizeof(char *));
	if (!new_envp)
		return (-1);
	tofree = *envp;
	i = -1;
	if (*envp)
	{
		while (++i < *(size_t *)nbr_exported)
		{
			if ((*envp)[i])
				new_envp[i] = (*envp)[i];
			else
			{
				i -= 1;
				*nbr_exported -= 1;
				*envp += 1;
			}
		}
		free(tofree);
	}
	*envp = new_envp;
	return (0);
}
