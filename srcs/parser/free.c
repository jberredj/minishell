/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:09:17 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 15:45:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_command.h"
#include "../libft/includes/ft_idllst.h"

void	free_command(void *content)
{
	t_command	*command;
	int			i;

	command = ft_idllst_content(content);
	if (command)
	{
		if (command->path_to_cmd)
			free(command->path_to_cmd);
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
		if (command->error)
			free(command->error);
		if (command->fd_in != 0)
			close(command->fd_in);
		if (command->fd_out != 1)
			close(command->fd_out);
		free(command);
	}
}
