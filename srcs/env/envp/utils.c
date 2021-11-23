/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:11:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 15:15:31 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_string.h"

char	**copy_envp(char **envp, int nbr)
{
	char	**copy;
	int		i;

	copy = (char **)ft_calloc(nbr + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		copy[i] = ft_strdup(envp[i]);
	return (copy);
}
