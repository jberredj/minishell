/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:28:00 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/21 11:55:10 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/includes/libft.h"
#include "structs/t_command.h"
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "env.h"
#include "tokeniser.h"
#include "parser.h"
#include "expander.h"
#include "minishell.h"
#include "exec.h"
#include "prompt.h"
/*
** REMOVE HEADER
*/
#include "_debug.h"

void	add_str_to_history(char *str)
{
	if (*str != ' ')
		add_history(str);
}

t_token	*get_tokens(char *str, t_env *env)
{
	t_token	*tokens;

	tokens = NULL;
	if (str)
	{
		if (*str)
		{
			add_str_to_history(str);
			tokens = tokenise_line(str);
			if (!tokens)
			{
				env->running = false;
				env->exit_code = 1;
			}
			free(str);
		}
	}
	else
	{
		write(1, "exit\n", 5);
		env->running = false;
	}
	return (tokens);
}

void	prompt(t_env *env)
{
	char		*prompt_str;
	char		*str;
	t_command	*commands;
	t_token		*tokens;

	env->running = true;
	while (env->running)
	{
		commands = NULL;
		prompt_str = get_prompt(env);
		str = readline(prompt_str);
		free(prompt_str);
		tokens = get_tokens(str, env);
		if (tokens)
		{
			expand_var(tokens, env);
			commands = generate_commands_from_tokens(env, tokens);
			ft_idllst_clear(&tokens->list, free_token);
		}
		if (commands)
		{
			exec_cmds(commands, env);
			ft_idllst_clear(&commands->list, free_command);
		}
	}
	rl_clear_history();
}
