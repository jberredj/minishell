/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:56:44 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 18:07:46 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "structs/t_command.h"
#include "../libft/includes/libft.h"
#include "exec.h"
#include "parser.h"
#include "env.h"
#include "minish_signal.h"
#include "error_codes.h"

int	get_exit_code(t_command *command, int status)
{
	if (WIFSIGNALED(status) == 1)
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("minishell: Quit (core dumped)", 2);
		else if (WTERMSIG(status) == SIGSEGV)
			ft_putstr_fd("Segmentation fault", 2);
		write(2, "\n", 1);
		command->exit_code = 128 + WTERMSIG(status);
	}
	else
		command->exit_code = WEXITSTATUS(status);
	return (0);
}

void	wait_childs(t_command *commands)
{
	int	status_code;

	while (commands)
	{
		if (commands->process > 0)
		{
			waitpid(commands->process, &status_code, 0);
			get_exit_code(commands, status_code);
		}
		commands = ft_idllst_next_content(&commands->list);
	}
}

static int	process_commands(t_command *commands, t_env *env)
{
	int	error;

	while (commands)
	{
		error = 0;
		error = treat_redirection(commands);
		if (error)
			closed_unused_fds(commands);
		if (error == CANCEL)
		{
			kill_launched_commands(commands);
			return (CANCEL);
		}
		if (!error && commands->builtin)
			error = exec_builtins(commands, env);
		else if (!error)
			error = exec_external(commands, env);
		error = 0;
		if (error)
			return (panic_exec_out(error, commands, env));
		commands = ft_idllst_next_content(&commands->list);
	}
	return (SUCCESS);
}

int	exec_cmds(t_command *commands, t_env *env)
{
	t_command	*monitor;
	int			error;

	monitor = commands;
	error = 0;
	if (exec_signals())
	{
		ft_putstr_fd("minishell: exec: fatal error: sigaction() failed", 2);
		return (CREATE_ERROR);
	}
	error = process_commands(commands, env);
	if (error)
		return (error);
	wait_childs(monitor);
	if (restore_minish_ctrl_c())
	{
		ft_putstr_fd("minishell: exec: fatal error: sigaction() failed", 2);
		return (CREATE_ERROR);
	}
	monitor = ft_idllst_content(ft_idllst_get_tail(&monitor->list));
	env->exit_code = monitor->exit_code;
	return (SUCCESS);
}
