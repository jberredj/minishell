/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:42:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 11:02:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	*ft_idllst_content(t_idllist *node)
{
	if (!ft_idllst_is_init(node))
		return (NULL);
	return (node->struct_addr);
}
