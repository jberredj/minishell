/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:07:42 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 17:23:41 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs/t_command.h"
#include "../libft/includes/ft_string.h"
#include "error_codes.h"

int	first_argv(t_command *cmd, char *content)
{
	char	**new_argv;

	new_argv = (char **)ft_calloc(2, sizeof(char *));
	if (!new_argv)
		return (ERR_MALLOC);
	new_argv[0] = ft_strdup(content);
	if (!new_argv[0])
	{
		free(new_argv);
		return (ERR_MALLOC);
	}
	cmd->argv = new_argv;
	cmd->argc = 1;
	return (SUCCESS);
}

static char	**copy_old_argv(char	**old_argv, int argc, int *i)
{
	char	**new_argv;

	new_argv = (char **)ft_calloc(argc + 2, sizeof(char *));
	if (!new_argv)
		return (NULL);
	while (old_argv[++(*i)])
	{
		new_argv[*i] = old_argv[*i];
		if (!new_argv[*i])
		{
			ft_free_split(new_argv, *i);
			return (NULL);
		}
	}
	return (new_argv);
}

int	add_to_command_argv(t_command *cmd, char *content)
{
	char	**new_argv;
	int		i;

	if (cmd->argc == 0)
		return (first_argv(cmd, content));
	i = -1;
	new_argv = copy_old_argv(cmd->argv, cmd->argc, &i);
	if (!new_argv)
		return (ERR_MALLOC);
	cmd->argc++;
	new_argv[i] = ft_strdup(content);
	if (!new_argv[i])
	{
		ft_free_split(new_argv, i);
		return (ERR_MALLOC);
	}
	free(cmd->argv);
	cmd->argv = new_argv;
	return (SUCCESS);
}
