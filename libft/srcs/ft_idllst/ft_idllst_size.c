/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:50:47 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 16:12:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"
#include <stdlib.h>

size_t	ft_idllst_size(t_idllist *node)
{
	if (!node)
		return (0);
	return (1 + ft_idllst_nbr_to_head(node) + ft_idllst_nbr_to_tail(node));
}
