/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:56:44 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/25 12:14:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "structs/t_command.h"
#include "../libft/includes/ft_idllst.h"

void	prep_fds(t_command *first, t_command *second)
{
	int	fds[2];

	if (first->pipe)
	{

	}
}

void	exec_command(t_command *commands)
{
	pid_t	child;
	int		fds[2];

	while (commands)
	{
		child = fork();
		if (child == 0)
		{
			free(sh_dat->env.envp);
			ft_idllst_clear(&sh_dat->env.env_vars->list, free_env_var);
			if (commands->path_to_cmd)
				execve(commands->path_to_cmd, commands->argv, commands->envp);
			else if (commands->builtin)
				commands->builtin(commands->argv, commands->envp);
			ft_idllst_clear(&commands->list, free_command);
			printf("FAILED EXECUTION\n");
			exit(1);
		}
	}
}
