/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:11:50 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/05 22:02:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_string.h"

char	**copy_envp(char **envp, int nbr)
{
	char	**copy;
	int		i;

	copy = (char **)ft_calloc(nbr + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = -1;
	while (envp && envp[++i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			ft_free_split(copy, i);
			return (NULL);
		}
	}
	return (copy);
}
