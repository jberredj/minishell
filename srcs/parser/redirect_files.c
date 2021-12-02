/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:06:10 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 19:09:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "structs/t_command.h"
#include "structs/t_token.h"
#include "error_codes.h"
#include "../libft/includes/ft_idllst.h"

int	infile_redirect(t_command *command, t_token **tokens)
{
	int	fd;

	*tokens = ft_idllst_next_content(&(*tokens)->list);
	if (access((*tokens)->content, F_OK) == 0)
	{
		if (access((*tokens)->content, R_OK) == 0)
		{
			fd = open((*tokens)->content, O_RDONLY);
			if (fd == -1)
				return (OPEN_ERROR | R_ERROR);
			if (command->fd_in != 0)
				close(command->fd_in);
			command->fd_in = fd;
			return (SUCCESS);
		}
		return (R_ERROR | FILE_ERROR);
	}
	return (NOT_EXIST_ERROR | FILE_ERROR);
}

int	outfile_redirect(t_command *command, t_token **tokens, int mode)
{
	int	fd;

	*tokens = ft_idllst_next_content(&(*tokens)->list);
	fd = open((*tokens)->content, O_CREAT | O_WRONLY | mode, 0644);
	if (fd == -1)
		return (CREATE_ERROR | FILE_ERROR);
	if (command->fd_out != 1)
		close(command->fd_out);
	command->fd_out = fd;
	return (SUCCESS);
}
