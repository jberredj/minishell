/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_get_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:42:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 16:44:24 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	*ft_idllst_get_content(t_idllist *node)
{
	if (!node)
		return (NULL);
	return ((void *)(node - node->struct_offset));
}
