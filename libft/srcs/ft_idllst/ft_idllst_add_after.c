/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_add_after.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:19:33 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 08:33:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	ft_idllst_add_after(t_idllist *new, t_idllist *node)
{
	t_idllist	*prev;
	t_idllist	*next;

	if (!ft_idllst_is_init(node) || !ft_idllst_is_init(new))
		return ;
	prev = node;
	next = node->next;
	if (next != prev)
	{
		next->prev = new;
		new->next = next;
	}
	new->prev = prev;
	prev->next = new;
}
