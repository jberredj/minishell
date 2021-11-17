/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_is_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:26:00 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 10:47:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_idllst.h"

bool	ft_idllst_is_init(t_idllist *node)
{
	if (!node || !node->prev || !node->next)
		return (false);
	return (true);
}
