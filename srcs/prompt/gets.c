/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 23:10:10 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/02 13:25:54 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/includes/libft.h"
#include "structs/t_command.h"
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "tokeniser.h"
#include "parser.h"
#include "expander.h"
#include "exec.h"
#include "prompt.h"
#include "error_codes.h"

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
			if (tokenise_line(&tokens, str) || expand_var(&tokens, env)
				|| combine_tokens(&tokens))
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

t_command	*get_commands(t_env *env, t_token *tokens)
{
	int			error;
	t_command	*commands;

	commands = NULL;
	error = generate_commands_from_tokens(env, tokens, &commands);
	if (error & FATAL_ERROR)
	{
		env->running = false;
		env->exit_code = 1;
	}
	ft_idllst_clear(&tokens->list, free_token);
	return (commands);
}
