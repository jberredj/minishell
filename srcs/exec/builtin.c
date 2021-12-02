/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:48:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 18:15:42 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "structs/t_command.h"

static void	swap_std_with_fds(t_command *command)
{
	if (command->fd_in != 0)
	{
		close(0);
		dup2(command->fd_in, 0);
		close(command->fd_in);
	}
	if (command->fd_out != 1)
	{
		close(1);
		dup2(command->fd_out, 1);
		close(command->fd_out);
	}
}

static void	restore_std(t_command *command, t_env *env)
{
	if (command->fd_in != 0)
	{
		close(0);
		dup2(env->stdin_copy, 0);
		command->fd_in = 0;
	}
	if (command->fd_out != 1)
	{
		close(1);
		dup2(env->stdout_copy, 1);
		command->fd_out = 1;
	}
}

void	exec_builtins(t_command *commands, t_env *env)
{
	commands->process = -2;
	swap_std_with_fds(commands);
	commands->exit_code = commands->builtin(commands->argv, env);
	restore_std(commands, env);
}
