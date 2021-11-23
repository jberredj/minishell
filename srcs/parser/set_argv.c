/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:07:42 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 15:31:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs/t_command.h"
#include "../libft/includes/ft_string.h"

void	add_to_command_argv(t_command *cmd, char *content)
{
	char	**new_argv;
	int		i;

	if (cmd->argc == 0)
	{
		cmd->argv = (char **)ft_calloc(2, sizeof(char *));
		cmd->argv[0] = content;
		cmd->argc = 1;
		return ;
	}
	new_argv = (char **)ft_calloc(cmd->argc + 2, sizeof(char *));
	i = -1;
	while (cmd->argv[++i])
		new_argv[i] = cmd->argv[i];
	cmd->argc++;
	new_argv[i] = ft_strdup(content);
	free(cmd->argv);
	cmd->argv = new_argv;
}
