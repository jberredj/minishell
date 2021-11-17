/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_add_before.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:46:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 08:35:58 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	ft_idllst_add_before(t_idllist *new, t_idllist *node)
{
	if (!ft_idllst_is_init(node) || !ft_idllst_is_init(new))
		return ;
	if (!ft_idllst_is_head(node))
		return (ft_idllst_add_after(new, node->prev));
	new->next = node;
	node->prev = new;
}
