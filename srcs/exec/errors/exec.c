/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:04:34 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 14:26:43 by jberredj         ###   ########.fr       */
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

void	kill_launched_commands(t_command *commands)
{
	t_command	*to_kill;

	to_kill = ft_idllst_content(ft_idllst_get_head(&commands->list));
	while (to_kill)
	{
		if (to_kill->process > 0)
			kill(to_kill->process, SIGQUIT);
		to_kill = ft_idllst_next_content(&to_kill->list);
	}
}

int	panic_exec_out(int error, t_command *commands, t_env *env)
{
	kill_launched_commands(commands);
	env->exit_code = 1;
	env->running = false;
	return (error);
}
