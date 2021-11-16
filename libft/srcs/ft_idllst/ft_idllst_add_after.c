/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_add_after.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:19:33 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 15:46:47 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	ft_idllst_add_after(t_idllist *new, t_idllist *node)
{
	t_idllist	*prev;
	t_idllist	*next;

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
