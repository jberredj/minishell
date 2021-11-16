/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_is_tail.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:37:30 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/16 16:46:51 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"
#include <stdbool.h>

bool	ft_idllst_is_tail(t_idllist *node)
{
	if (!node)
		return (false);
	return ((bool)(node == node->next));
}
