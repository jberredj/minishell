/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:42:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 08:57:56 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	*ft_idllst_content(t_idllist *node)
{
	if (!ft_idllst_is_init(node))
		return (NULL);
	return ((void *)(node - node->struct_offset));
}
