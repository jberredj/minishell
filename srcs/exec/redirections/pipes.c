/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:53:25 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/29 00:00:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/includes/ft_idllst.h"
#include "structs/t_command.h"
#include "error_codes.h"

int	create_pipe(t_command *command)
{
	int			fds[2];
	t_command	*next_command;

	if (!command->piped)
		return (SUCCESS);
	if (pipe(fds))
		return (CREATE_ERROR | PIPE_ERROR);
	next_command = ft_idllst_next_content(&command->list);
	if (command->fd_out == 1)
		command->fd_out = fds[1];
	else
		close(fds[1]);
	if (next_command->fd_in == 0)
		next_command->fd_in = fds[0];
	else
		close(fds[0]);
	return (SUCCESS);
}
