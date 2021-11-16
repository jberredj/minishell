/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:08:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 15:11:48 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_idllst.h"

t_idllist	ft_init_idllst(t_idllist *list, void *struct_addr)
{
	return ((t_idllist){
		.prev = list,
		.next = list,
		.struct_offset = ((ptrdiff_t)list - (ptrdiff_t)struct_addr)
	});
}
