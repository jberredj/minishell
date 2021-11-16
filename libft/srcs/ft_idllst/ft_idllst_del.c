/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:53:44 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 17:00:55 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

t_idllist	*ft_idllst_del(t_idllist *node, void (*del)(void*))
{
	if (!node || !del)
		return (NULL);
	return (ft_idllst_pop(node, del));
}
