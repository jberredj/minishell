/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:09:17 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/04 18:58:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../libft/includes/ft_idllst.h"
#include "structs/t_command.h"

void	free_xv(char **xv)
{
	int	i;

	i = -1;
	if (xv)
	{
		while (xv[++i])
			free(xv[i]);
		free(xv);
	}
}

void	free_command(void *content)
{
	t_command	*command;

	command = ft_idllst_content(content);
	if (command)
	{
		if (command->path_to_cmd)
			free(command->path_to_cmd);
		if (command->argv)
			free_xv(command->argv);
		if (command->envp)
			free_xv(command->envp);
		if (command->in_file)
			free(command->in_file);
		if (command->out_file)
			free(command->out_file);
		if (command->fd_in != 0)
			close(command->fd_in);
		if (command->fd_out != 1)
			close(command->fd_out);
		free(command);
	}
}
