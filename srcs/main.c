/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 20:25:53 by jberredj         ###   ########.fr       */
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
#include "error_codes.h"

void	print_motd(void)
{
	ft_putendl_fd("\033[0;32m|\\/| .  _  .  _ |_   _ | |\033[0;0m", 1);
	ft_putstr_fd("\033[0;32m|  | | | | | _) | | (- | |\033[0;0m", 1);
	ft_putendl_fd(" Authors : ddiakova & jberredj", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_env				env;

	(void)argc;
	(void)argv;
	if (init_sh(&env, envp))
		return (1);
	print_motd();
	prompt(&env);
	free(env.envp);
	if (env.env_vars)
		ft_idllst_clear(&env.env_vars->list, free_env_var);
	close(env.stdin_copy);
	close(env.stdout_copy);
	return (env.exit_code);
}
