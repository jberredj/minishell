/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:03:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/12 20:25:44 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "structs/t_command.h"
#include "../libft/includes/libft.h"
#include "exec.h"
#include "parser.h"
#include "env.h"
#include <stdio.h>

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

int	print_exec_error(char *path)
{
	int	fd;

	if (access(path, F_OK) == 0)
	{
		fd = open(path, __O_DIRECTORY);
		if (fd)
		{
			close(fd);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": Is a directory", 2);
		}
		else if (access(path, X_OK) != 0)
			perror(path);
		return (126);
	}
	else
		perror(path);
	return (127);
}

static void	child_process(t_command *commands, t_env *env)
{
	t_command	*to_exec;
	t_command	*to_free;
	int			error;

	to_free = get_to_free(commands);
	to_exec = ft_idllst_content(ft_idllst_pop(&commands->list, NULL));
	clean_all_exec(to_free, env);
	swap_std_with_fds(to_exec);
	execve(to_exec->path_to_cmd, to_exec->argv, to_exec->envp);
	error = print_exec_error(to_exec->path_to_cmd);
	free_command(&to_exec->list);
	exit(error);
}

void	exec_external(t_command *commands, t_env *env)
{
	commands->process = fork();
	if (commands->process == 0)
		child_process(commands, env);
	else
		closed_unused_fds(commands);
}
