/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:04:18 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 10:47:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

int	ft_lstpop(t_list **alst, t_list *elem, void (*del)(void*))
{
	t_list	*last;
	t_list	*current;

	last = NULL;
	if (!alst || !*alst || !elem || !del)
		return (1);
	current = *alst;
	while (current)
	{
		if (current == elem)
		{
			if (*alst == current)
				*alst = current->next;
			else
				last->next = current->next;
			ft_lstdelone(current, del);
			return (0);
		}
		last = current;
		current = current->next;
	}
	return (1);
}
