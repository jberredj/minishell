/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_prev_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:00:01 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 10:47:27 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	*ft_idllst_prev_content(t_idllist *node)
{
	if (!ft_idllst_is_init(node) || ft_idllst_is_head(node))
		return (NULL);
	return (ft_idllst_content(node->prev));
}
