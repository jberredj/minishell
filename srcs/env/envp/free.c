/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:43:16 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 20:41:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_idllst.h"
#include "error_codes.h"

static char	**search_deleted_shift_envp(char ***envp, size_t *nbr_exported)
{
	char	**tofree;
	char	**new_envp;
	int		i;

	new_envp = (char **)ft_calloc(*nbr_exported, sizeof(char *));
	if (!new_envp)
		return (NULL);
	tofree = *envp;
	i = -1;
	if (*envp)
	{
		while (++i < *(int *)nbr_exported)
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
	return (new_envp);
}

int	remove_from_envp(char ***envp, size_t *nbr_exported)
{
	char	**buff;

	buff = search_deleted_shift_envp(envp, nbr_exported);
	if (!buff)
		return (ERR_MALLOC);
	*envp = buff;
	return (0);
}
