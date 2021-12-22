/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:40:34 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 17:37:56 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "structs/t_command.h"
#include "../libft/includes/libft.h"
#include "exec.h"
#include "parser.h"
#include "env.h"
#include <stdio.h>
#include <signal.h>
#include "error_codes.h"

int	check_file(char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY);
	if (fd)
	{
		close(fd);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
	else if (access(path, X_OK) != 0)
		perror(path);
	return (126);
}

int	print_exec_error(char *path, bool had_env_path)
{
	if (access(path, F_OK) == 0)
		return (check_file(path));
	else if (!had_env_path || ft_strchr(path, '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
	}
	else
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": command not found", 2);
	}
	return (127);
}

int	panic_child_out(int error, t_command *command)
{
	ft_putstr_fd("minishell: ", 2);
	if (error == FILE_ERROR)
		perror(command->path_to_cmd);
	if (error & (CREATE_ERROR | ERR_MALLOC))
		ft_putstr_fd(command->path_to_cmd, 2);
	if (error == CREATE_ERROR)
		ft_putstr_fd(": fatal error: sigaction() failed", 2);
	if (error == ERR_MALLOC)
		ft_putstr_fd(": fatal error: malloc() failed", 2);
	free_command(&command->list);
	return (1);
}
