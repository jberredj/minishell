/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_clear_after.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:56:54 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 08:40:04 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_idllst.h"

void	ft_idllst_clear_after(t_idllist *node, void (*del)(void*),
		bool include_current)
{
	t_idllist	*next;
	t_idllist	*to_pop;

	if (!ft_idllst_is_init(node) || !del)
		return ;
	if (include_current)
		to_pop = node;
	else
		to_pop = node->next;
	while (!ft_idllst_is_tail(to_pop))
	{
		next = to_pop->next;
		ft_idllst_pop(to_pop, del);
		to_pop = next;
	}
	ft_idllst_pop(to_pop, del);
}
