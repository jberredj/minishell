/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:56:44 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/16 12:40:18 by jberredj         ###   ########.fr       */
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

int	get_exit_code(t_command *command, int status)
{
	if (WIFSIGNALED(status) == 1)
	{
		int debug = WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("minishell: Quit (core dumped)", 2);
		else if (WTERMSIG(status) == SIGSEGV)
			ft_putendl_fd("Segmentation fault", 2);
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

void	ctrl_c_exec(int sig, siginfo_t *info, void *ctx)
{
	(void)sig;
	(void)info;
	(void)ctx;
	write(1, "\n", 1);
}

static void	exec_signals(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_sigaction = ctrl_c_exec;
	sigaction(SIGINT, &sig, NULL);
}

void	restore_minish_ctrl_c(void)
{
	struct sigaction	sigint_act;

	ft_bzero(&sigint_act, sizeof(struct sigaction));
	sigint_act.sa_sigaction = ctrl_c;
	sigaction(SIGINT, &sigint_act, NULL);
}

void	exec_cmds(t_command *commands, t_env *env)
{
	t_command	*monitor;

	monitor = commands;
	exec_signals();
	while (commands)
	{
		if (commands->builtin)
			exec_builtins(commands, env);
		else
			exec_external(commands, env);
		commands = ft_idllst_next_content(&commands->list);
	}
	wait_childs(monitor);
	restore_minish_ctrl_c();
	monitor = ft_idllst_content(ft_idllst_get_tail(&monitor->list));
	env->exit_code = monitor->exit_code;
}
