/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:06:10 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 15:59:04 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "structs/t_command.h"
#include "structs/t_token.h"
#include "error_codes.h"
#include "../libft/includes/ft_idllst.h"

int	infile_redirect(t_command *command)
{
	int		fd;

	if (!command->in_file)
		return (SUCCESS);
	if (access(command->in_file, F_OK) == 0)
	{
		if (access(command->in_file, R_OK) == 0)
		{
			fd = open(command->in_file, O_RDONLY);
			if (fd == -1)
				return (OPEN_ERROR | R_ERROR);
			if (command->fd_in != 0)
				close(command->fd_in);
			command->fd_in = fd;
			return (SUCCESS);
		}
		return (R_ERROR | FILE_ERROR);
	}
	return (NOT_EXIST | FILE_ERROR);
}

int	outfile_redirect(t_command *command)
{
	int	fd;

	if (!command->out_file)
		return (SUCCESS);
	fd = open(command->out_file, O_CREAT | O_WRONLY | command->out_mode, 0644);
	if (fd == -1)
		return (CREATE_ERROR | FILE_ERROR);
	if (command->fd_out != 1)
		close(command->fd_out);
	command->fd_out = fd;
	return (SUCCESS);
}
