/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_clear_before.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:56:54 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 17:38:33 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	ft_idllst_clear_before(t_idllist *node, void (*del)(void*),
		bool include_current)
{
	t_idllist	*prev;
	t_idllist	*to_pop;

	if (!node || !del)
		return ;
	if (include_current)
		to_pop = node;
	else
		to_pop = node->prev;
	while (!ft_idllst_is_head(to_pop))
	{
		prev = to_pop->prev;
		ft_idllst_pop(to_pop, del);
		to_pop = prev;
	}
	ft_idllst_pop(to_pop, del);
}
