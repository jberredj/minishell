/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 20:09:49 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/28 23:03:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../libft/includes/libft.h"
#include "env.h"
#include "error_codes.h"

void	ctrl_c(int sig, siginfo_t *info, void *ctx)
{
	(void)sig;
	(void)info;
	(void)ctx;
	write(1, "\n", 1);
	close(0);
}

int	setup_signal(void)
{
	struct sigaction	sigquit_act;
	struct sigaction	sigint_act;

	ft_bzero(&sigquit_act, sizeof(struct sigaction));
	sigquit_act.sa_sigaction = NULL;
	sigquit_act.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sigquit_act, NULL) == -1)
		return (ERR_MALLOC);
	ft_bzero(&sigint_act, sizeof(struct sigaction));
	sigint_act.sa_sigaction = ctrl_c;
	if (sigaction(SIGINT, &sigint_act, NULL) == -1)
		return (ERR_MALLOC);
	return (SUCCESS);
}

int	copy_std_fds(t_env *env)
{
	env->stdin_copy = dup(0);
	if (env->stdin_copy == -1)
		return (1);
	env->stdout_copy = dup(1);
	if (env->stdout_copy == -1)
	{
		close (env->stdin_copy);
		return (1);
	}
	return (SUCCESS);
}

int	init_sh(t_env *env, char **envp)
{
	int	error;

	ft_bzero(env, sizeof(t_env));
	if (setup_signal())
	{
		ft_putendl_fd("minishell: init_sh: fatal error: malloc() failed", 2);
		return (1);
	}
	if (copy_std_fds(env))
	{
		ft_putendl_fd("minishell: init_sh: fatal error: dup() failed", 2);
		return (1);
	}
	error = parse_herited_envp(env, envp);
	if (error)
	{
		if (error == ERR_MALLOC)
			ft_putendl_fd("minishell: init_sh: fatal error: \
malloc() failed", 2);
		return (error);
	}
	return (SUCCESS);
}
