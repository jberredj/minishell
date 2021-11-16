/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_get_tail.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:21:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 16:46:13 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

t_idllist	*ft_idllst_get_tail(t_idllist *node)
{
	if (!node)
		return (NULL);
	if (!ft_idllst_is_tail(node))
		while (node != node->next)
			node = node->next;
	return (node);
}
