/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_next_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:00:01 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 09:00:20 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	*ft_idllst_next_content(t_idllist *node)
{
	if (!ft_idllst_is_init(node) || ft_idllst_is_tail(node))
		return (NULL);
	return (ft_idllst_content(node->next));
}
