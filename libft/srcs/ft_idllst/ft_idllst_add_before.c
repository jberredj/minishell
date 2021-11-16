/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_add_before.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:46:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 15:17:37 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"

void	ft_idllst_add_before(t_idllist *new, t_idllist *head)
{
	if (head->prev != head)
		return (ft_idllst_add_after(new, head->prev));
	new->next = head;
	head->prev = new;
}
