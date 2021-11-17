/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:08:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 11:02:19 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_idllst.h"

t_idllist	ft_idllst_init(t_idllist *list, void *struct_addr)
{
	return ((t_idllist){
		.prev = list,
		.next = list,
		.struct_addr = struct_addr
	});
}
