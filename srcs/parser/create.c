/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:59:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 18:30:25 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_command.h"
#include "../libft/includes/ft_idllst.h"

t_command	*new_command_add(t_command *command)
{
	t_command	*new;

	new = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!new)
		return (NULL);
	new->list = ft_idllst_init(&new->list, new);
	if (!command)
		return (new);
	else
		ft_idllst_add_back(&new->list, &command->list);
	return (new);
}
