/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_add_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:43:24 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 15:48:03 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	ft_idllst_add_back(t_idllist *new, t_idllist *list)
{
	t_idllist	*tail;

	tail = ft_idllst_get_tail(list);
	ft_idllst_add_after(new, tail);
}
