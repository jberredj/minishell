/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:04:34 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 11:07:51 by jberredj         ###   ########.fr       */
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

int	panic_exec_out(int error, t_command *commands, t_env *env)
{
	t_command	*command;

	command = commands;
	while (command)
	{
		if (command->process > 0)
			kill(command->process, SIGQUIT);
		command = ft_idllst_next_content(&command->list);
	}
	env->exit_code = 1;
	env->running = false;
	return (error);
}