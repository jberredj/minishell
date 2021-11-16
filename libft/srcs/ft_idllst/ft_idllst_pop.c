/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:15:49 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 17:05:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

t_idllist	*ft_idllst_pop(t_idllist *node, void (*del)(void*))
{
	t_idllist	*poped;

	if (!node)
		return (NULL);
	poped = node;
	if (ft_idllst_is_head(node))
		node->next->prev = node->next;
	else
		node->next->prev = node->prev;
	if (ft_idllst_is_tail(node))
		node->prev->next = node->prev;
	else
		node->prev->next = node->next;
	if (del)
	{
		del(poped);
		poped = NULL;
	}
	return (poped);
}