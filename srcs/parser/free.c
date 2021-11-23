/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:09:17 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 16:28:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs/t_command.h"
#include "../libft/includes/ft_idllst.h"

void	free_command(void *content)
{
	t_command	*command;
	int			i;

	command = ft_idllst_content(content);
	if (command)
	{
		if (command->argv)
		{
			i = -1;
			while (command->argv[++i])
				free(command->argv[i]);
			free(command->argv);
		}
		if (command->envp)
		{
			i = -1;
			while (command->envp[++i])
				free(command->envp[i]);
			free(command->envp);
		}
		free(command);
	}
}
