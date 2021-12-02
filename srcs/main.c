/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 14:36:47 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../libft/includes/libft.h"
#include "env.h"
#include "minishell.h"
#include "prompt.h"
#include <readline/readline.h>
#include <readline/history.h>

void	print_motd(void)
{
	printf("\033[0;32m|\\/| .  _  .  _ |_   _ | |\033[0;0m");
	printf(" Version : " VERSION_NUMBER);
	printf("\n");
	printf("\033[0;32m|  | | | | | _) | | (- | |\033[0;0m");
	printf(" Authors : ddiakova & jberredj\n");
#ifdef DEBUG
	printf("\033[1;33m/!\\ WARNING THIS A DEBUG BUILD, PERFORMANCE MAY BE BAD, OR EVERYTHING CAN JUST COLLASPE ON ITSELF OUT OF NOWHERE /!\\\033[0;0m\n");
#endif
}

void	ctrl_c(int sig, siginfo_t *info, void *ctx)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal()
{
	struct sigaction	sigquit_act;
	struct sigaction	sigint_act;

	ft_bzero(&sigquit_act, sizeof(struct sigaction));
	sigquit_act.sa_sigaction = NULL;
	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
	ft_bzero(&sigint_act, sizeof(struct sigaction));
	sigint_act.sa_sigaction = ctrl_c;
	sigaction(SIGINT, &sigint_act, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_env				env;

	(void)argc;
	(void)argv;
	ft_bzero(&env, sizeof(t_env));
	setup_signal();
	env.stdin_copy = dup(0);
	env.stdout_copy = dup(1);
	parse_herited_envp(&env, envp);
	print_motd();
	prompt(&env);
	free(env.envp);
	ft_idllst_clear(&env.env_vars->list, free_env_var);
	close(env.stdin_copy);
	close(env.stdout_copy);
	return (env.exit_code);
}
