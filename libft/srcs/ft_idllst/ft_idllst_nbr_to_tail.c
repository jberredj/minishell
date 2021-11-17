/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_nbr_to_tail.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:55:21 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 08:54:16 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"
#include <stdlib.h>

size_t	ft_idllst_nbr_to_tail(t_idllist *node)
{
	size_t	i;

	if (!ft_idllst_is_init(node))
		return (0);
	i = 0;
	while (node != node->next)
	{
		i++;
		node = node->next;
	}
	return (i);
}
