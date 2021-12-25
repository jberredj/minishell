/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:43:25 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 20:55:08 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/includes/libft.h"
#include "structs/t_command.h"
#include "error_codes.h"
#include "exec.h"

typedef int	(*t_redirect_func)(t_command *);

int	pipe_error(int error)
{
	if (error & CREATE_ERROR)
		perror("minishell: pipes");
	return (CANCEL);
}

t_redirect_func	select_func(int nbr, t_command *command)
{
	if ((nbr == 1 && command->last_found == OUTFILE)
		|| (nbr == 2 && command->last_found == INFILE))
		return (infile_redirect);
	return (outfile_redirect);
}

int	redirect_error(int error, t_command *command, t_redirect_func way)
{
	char	*file;

	if (error & (FILE_ERROR | OPEN_ERROR))
	{
		ft_putstr_fd("minishell: ", 2);
		if (way == infile_redirect)
			file = command->in_file;
		else
			file = command->out_file;
		perror(file);
	}
	return (SKIP);
}

int	treat_redirection(t_command *command)
{
	int				error;
	t_redirect_func	redirect_file;
	int				i;

	error = create_pipe(command);
	if (error)
		return (pipe_error(error));
	i = 0;
	while (++i < 3)
	{
		redirect_file = select_func(i, command);
		error = redirect_file(command);
		if (error)
			return (redirect_error(error, command, redirect_file));
	}
	return (SUCCESS);
}
