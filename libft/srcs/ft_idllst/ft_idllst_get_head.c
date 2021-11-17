/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_get_head.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:21:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 08:52:29 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

t_idllist	*ft_idllst_get_head(t_idllist *node)
{
	if (!ft_idllst_is_init(node))
		return (NULL);
	if (!ft_idllst_is_head(node))
		while (node != node->prev)
			node = node->prev;
	return (node);
}
