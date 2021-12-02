/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:56:44 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 19:33:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "structs/t_command.h"
#include "../libft/includes/libft.h"
#include "exec.h"
#include "parser.h"
#include "env.h"

int	get_exit_code(t_command *command, int status)
{
	if (WIFSIGNALED(status) == 1)
	{
		if (WTERMSIG(status) == 2)
		{
			command->exit_code = 130;
		}
		else if (WTERMSIG(status) == 3)
		{
			ft_putendl_fd("minishell :Quit (core dumped)\n", 2);
			command->exit_code = 131;
		}
	}
	else
		command->exit_code = status;
	return (0);
}

void	wait_childs(t_command *commands)
{
	int	status_code;

	while (commands)
	{
		if (commands->process > 0)
		{
			waitpid(-1, &status_code, WUNTRACED);
			get_exit_code(commands, status_code);
		}
		commands = ft_idllst_next_content(&commands->list);
	}
}

void	exec_cmds(t_command *commands, t_env *env)
{
	t_command	*monitor;

	monitor = commands;
	while (commands)
	{
		if (commands->builtin)
			exec_builtins(commands, env);
		else
			exec_external(commands, env);
		commands = ft_idllst_next_content(&commands->list);
	}
	wait_childs(monitor);
}
