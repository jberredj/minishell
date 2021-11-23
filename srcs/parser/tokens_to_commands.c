/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:21:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 16:33:56 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "structs/t_command.h"
#include "structs/t_token.h"
#include "structs/t_env.h"
#include "../libft/includes/ft_idllst.h"
#include "builtin.h"
#include "env.h"
#include "parser.h"

static t_command	*init_new_command(t_env *env, t_token *tokens,
					t_command *commands, bool *new_command)
{
	commands = new_command_add(commands);
	check_builtin(commands, env->path, *tokens);
	add_to_command_argv(commands, commands->path_to_cmd);
	commands->envp = copy_envp(env->envp, env->nbr_exported);
	*new_command = false;
	return (commands);
}

t_command	*generate_commands_from_tokens(t_env *env, t_token *tokens)
{
	t_command	*commands;
	bool		new_command;

	commands = NULL;
	new_command = true;
	while (tokens)
	{
		if (new_command)
			commands = init_new_command(env, tokens, commands, &new_command);
		else
		{
			if (tokens->type == SEPARATOR)
			{
				new_command = true;
				continue ; // Implement true separator handle
			}
			add_to_command_argv(commands, tokens->content);
		}
		tokens = ft_idllst_next_content(&tokens->list);
	}
	return (commands);
}
