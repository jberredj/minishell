/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:11:56 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/22 17:35:58 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	ft_idllst_clear(t_idllist *node, void (*del)(void*))
{
	if (!ft_idllst_is_init(node) || !del)
		return ;
	if (ft_idllst_is_head(node) && !ft_idllst_is_tail(node))
		ft_idllst_clear_after(node, del, false);
	else if (ft_idllst_is_tail(node) && !ft_idllst_is_head(node))
		ft_idllst_clear_before(node, del, false);
	else if (!ft_idllst_is_head(node) && !ft_idllst_is_tail(node))
	{
		ft_idllst_clear_before(node, del, false);
		ft_idllst_clear_after(node, del, false);
	}
	ft_idllst_del(node, del);
}
