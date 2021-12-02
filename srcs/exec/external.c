/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:03:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 19:33:33 by jberredj         ###   ########.fr       */
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

static void	clean_all_before_exec(t_command *commands, t_env *env)
{
	close(env->stdin_copy);
	close(env->stdout_copy);
	if (commands)
		ft_idllst_clear(&commands->list, free_command);
	ft_idllst_clear(&env->env_vars->list, free_env_var);
}

static t_command	*get_to_free(t_command *commands)
{
	t_command	*next;
	t_command	*prev;

	next = ft_idllst_next_content(&commands->list);
	prev = ft_idllst_prev_content(&commands->list);
	if (prev)
		return (prev);
	return (next);
}

static void	child_process(t_command *commands, t_env *env)
{
	t_command	*to_exec;
	t_command	*to_free;

	to_free = get_to_free(commands);
	to_exec = ft_idllst_content(ft_idllst_pop(&commands->list, NULL));
	clean_all_before_exec(to_free, env);
	if (to_exec->fd_in != 0)
	{
		dup2(to_exec->fd_in, 0);
		close(to_exec->fd_in);
	}
	if (to_exec->fd_out != 1)
	{
		dup2(to_exec->fd_out, 1);
		close(to_exec->fd_out);
	}
	execve(to_exec->path_to_cmd, to_exec->argv, to_exec->envp);
	exit (1);
}

void	exec_external(t_command *commands, t_env *env)
{
	commands->process = fork();
	if (commands->process == 0)
		child_process(commands, env);
	else
	{
		if (commands->fd_in != 0)
		{
			close(commands->fd_in);
			commands->fd_in = 0;
		}
		if (commands->fd_out != 1)
		{
			close(commands->fd_out);
			commands->fd_out = 1;
		}
	}
}
