/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:34:24 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 21:41:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "structs/t_command.h"
#include "structs/t_env.h"
#include "env.h"
#include "parser.h"
#include "error_codes.h"

int	swap_std_with_fds(t_command *command)
{
	int	error;

	error = 0;
	if (command->fd_in != 0)
	{
		close(0);
		error = dup2(command->fd_in, 0);
		close(command->fd_in);
		if (error == -1)
			return (CREATE_ERROR);
	}
	if (command->fd_out != 1)
	{
		close(1);
		error = dup2(command->fd_out, 1);
		close(command->fd_out);
		if (error == -1)
			return (CREATE_ERROR);
	}
	return (SUCCESS);
}

void	close_unused_fds(t_command *command)
{
	if (command->fd_in != 0)
	{
		close(command->fd_in);
		command->fd_in = 0;
	}
	if (command->fd_out != 1)
	{
		close(command->fd_out);
		command->fd_out = 1;
	}
}

void	clean_all_exec(t_command *commands, t_env *env)
{
	close(env->stdin_copy);
	close(env->stdout_copy);
	if (commands)
		ft_idllst_clear(&commands->list, free_command);
	if (env->env_vars)
		ft_idllst_clear(&env->env_vars->list, free_env_var);
	free(env->envp);
	rl_clear_history();
}
