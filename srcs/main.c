/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 19:35:06 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../libft/includes/libft.h"
#include "env.h"
#include "minishell.h"
#include "prompt.h"

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


int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sigquit_act;
	t_sh_dat			sh_dat;

	(void)argc;
	(void)argv;
	ft_bzero(&sigquit_act, sizeof(struct sigaction));
	sigquit_act.sa_sigaction = NULL;
	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
	ft_bzero(&sh_dat, sizeof(t_sh_dat));
	parse_herited_envp(&sh_dat.env, envp);
	print_motd();
	prompt(&sh_dat);
	free(sh_dat.env.envp);
	ft_idllst_clear(&sh_dat.env.env_vars->list, free_env_var);
	return (0);
}
