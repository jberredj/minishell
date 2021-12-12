/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:48:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/06 17:55:22 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../libft/includes/ft_idllst.h"
#include "parser.h"
#include "env.h"
#include "structs/t_command.h"
#include "exec.h"
#include "error_codes.h"
#include "minishell_error.h"

static void	restore_std_fds(t_command *command, t_env *env)
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

void	exec_builtins(t_command *commands, t_env *env)
{
	commands->process = need_fork(commands);
	if (commands->process == 0 || commands->process == -2)
	{
		swap_std_with_fds(commands);
		commands->exit_code = commands->builtin(commands->argv, env);
		commands->exit_code = minishell_error(commands->exit_code, commands->argv[1]);
		if (commands->process == -2)
			restore_std_fds(commands, env);
		else
			exit_forked_builtin(commands, env);
	}
	else
		closed_unused_fds(commands);
}
