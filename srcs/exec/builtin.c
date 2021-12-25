/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:48:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 21:41:37 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../libft/includes/libft.h"
#include "structs/t_command.h"
#include "error_codes.h"
#include "exec.h"

static int	restore_std_fds(t_command *command, t_env *env)
{
	if (command->fd_in != 0)
	{
		close(0);
		if (dup2(env->stdin_copy, 0) == -1)
			return (FILE_ERROR);
		command->fd_in = 0;
	}
	if (command->fd_out != 1)
	{
		close(1);
		if (dup2(env->stdout_copy, 1) == -1)
			return (FILE_ERROR);
		command->fd_out = 1;
	}
	return (SUCCESS);
}

pid_t	need_fork(t_command *commands)
{
	if (ft_idllst_size(&commands->list) == 1)
		return (-2);
	return (fork());
}

void	exit_forked_builtin(t_command *commands, t_env *env)
{
	int	exit_code;

	exit_code = commands->exit_code;
	clean_all_exec(commands, env);
	exit(exit_code);
}

int	exec_builtin_wrapper(t_command *commands, t_env *env)
{
	commands->exit_code = commands->builtin(commands->argv, env);
	if (env->error_in_builtin)
	{
		env->running = false;
		panic_builtin_out(env->error_in_builtin, commands);
		return (env->error_in_builtin);
	}
	return (SUCCESS);
}

int	exec_builtins(t_command *commands, t_env *env)
{
	int	error;

	error = SUCCESS;
	commands->process = need_fork(commands);
	if (commands->process == 0 || commands->process == -2)
	{
		if (!swap_std_with_fds(commands))
			error = exec_builtin_wrapper(commands, env);
		else
			error = panic_builtin_out(CREATE_ERROR | 1, commands);
		if (commands->process == -2)
		{
			if (restore_std_fds(commands, env))
				error = panic_builtin_out(CREATE_ERROR, commands);
		}
		else
			exit_forked_builtin(commands, env);
	}
	else
		close_unused_fds(commands);
	if (commands->process == -1)
		error = panic_builtin_out(CREATE_ERROR | 2, commands);
	return (error);
}
