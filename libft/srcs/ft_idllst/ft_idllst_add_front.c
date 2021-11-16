/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_add_front.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:43:24 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 15:46:22 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	ft_idllst_add_front(t_idllist *new, t_idllist *list)
{
	t_idllist	*head;

	head = ft_idllst_get_head(list);
	ft_idllst_add_before(new, head);
}
