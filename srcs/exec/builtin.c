/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:48:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 15:14:33 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "structs/t_command.h"

void	exec_builtins(t_command *commands, t_env *env)
{
	commands->process = -2;
	if (commands->fd_in != 0)
	{
		close(0);
		dup2(commands->fd_in, 0);
		close(commands->fd_in);
	}
	if (commands->fd_out != 1)
	{
		close(1);
		dup2(commands->fd_out, 1);
		close(commands->fd_out);
	}
	commands->exit_code = commands->builtin(commands->argv, env);
	if (commands->fd_in != 0)
	{
		close(0);
		dup2(env->stdin_copy, 0);
		commands->fd_in = 0;
	}
	if (commands->fd_out != 1)
	{
		close(1);
		dup2(env->stdout_copy, 1);
		commands->fd_out = 1;
	}
}
