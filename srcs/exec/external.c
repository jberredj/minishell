/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:03:59 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/06 00:20:23 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/includes/libft.h"
#include "structs/t_command.h"
#include "exec.h"
#include "parser.h"
#include "env.h"
#include "error_codes.h"
#include "minish_signal.h"

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

static char	*try_exec_command(t_command *command)
{
	char	*path_to_cmd;
	char	**argv;
	char	**envp;
	int		fds[2];

	path_to_cmd = command->path_to_cmd;
	argv = command->argv;
	envp = command->envp;
	fds[0] = command->fd_in;
	fds[1] = command->fd_out;
	if (command->in_file)
		free(command->in_file);
	if (command->out_file)
		free(command->out_file);
	free(command);
	if (path_to_cmd)
		execve(path_to_cmd, argv, envp);
	if (fds[0] != 0)
		close(fds[0]);
	if (fds[1] != 1)
		close(fds[1]);
	free_xv(argv);
	free_xv(envp);
	return (path_to_cmd);
}

static int	underscore_var(t_env *env, char *path_to_cmd)
{
	t_env_var	*node;

	node = find_env_var_in_lst(env->env_vars, "_");
	if (!node)
		return (create_exported_var(env, "_", path_to_cmd));
	if (update_env_var_value(node, path_to_cmd))
		return (ERR_MALLOC);
	if (!env_var_to_envp(&env->envp, node, &env->nbr_exported))
		return (ERR_MALLOC);
	return (SUCCESS);
}

static int	child_process(t_command *commands, t_env *env)
{
	t_command	*to_exec;
	t_command	*to_free;
	int			error;
	bool		had_env_path;
	char		*path_to_cmd;

	to_free = get_to_free(commands);
	to_exec = ft_idllst_content(ft_idllst_pop(&commands->list, NULL));
	had_env_path = (env->path && *env->path->value);
	if (commands->path_to_cmd)
		if (underscore_var(env, commands->path_to_cmd))
			return (panic_child_out(ERR_MALLOC, to_exec));
	to_exec->envp = copy_envp(env->envp, env->nbr_exported);
	if (!to_exec->envp)
		return (panic_child_out(ERR_MALLOC, to_exec));
	clean_all_exec(to_free, env);
	if (swap_std_with_fds(to_exec))
		return (panic_child_out(FILE_ERROR, to_exec));
	if (restore_external_signals())
		return (panic_child_out(CREATE_ERROR, to_exec));
	path_to_cmd = try_exec_command(to_exec);
	error = print_exec_error(path_to_cmd, had_env_path);
	free(path_to_cmd);
	return (error);
}

int	exec_external(t_command *commands, t_env *env)
{
	commands->process = fork();
	if (commands->process == 0)
		exit(child_process(commands, env));
	else
		close_unused_fds(commands);
	if (commands->process == -1)
	{
		ft_putstr_fd("minishell: exec: ", 2);
		ft_putstr_fd(commands->argv[0], 2);
		perror(": fatal error");
		return (CREATE_ERROR);
	}
	return (SUCCESS);
}
