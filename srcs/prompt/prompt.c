/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:28:00 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/29 17:15:22 by jberredj         ###   ########.fr       */
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

int	prompt_str_error(t_env *env)
{
	env->exit_code = 1;
	ft_putendl_fd("minishell: prompt_str: malloc() failed", 2);
	return (ERR_MALLOC);
}

int	ctrl_c_prompt(char **str, t_env *env)
{
	if (dup2(env->stdin_copy, 0))
	{
		env->exit_code = 1;
		ft_putendl_fd("minishell: prompt: fatal error: dup2() failed", 2);
		return (CREATE_ERROR);
	}
	*str = ft_strdup("");
	if (!*str)
	{
		env->exit_code = 1;
		ft_putendl_fd("minishell: prompt: fatal error: malloc() failed", 2);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

int	get_user_str(char **str, t_env *env)
{
	char		*prompt_str;

	prompt_str = get_prompt(env);
	if (!prompt_str)
		return (prompt_str_error(env));
	*str = readline(prompt_str);
	if (read(0, NULL, 0) == -1)
		if (ctrl_c_prompt(str, env))
			return (SUCCESS);
	free(prompt_str);
	return (SUCCESS);
}

int	prompt(t_env *env)
{
	int			error;
	char		*str;
	t_command	*commands;
	t_token		*tokens;

	env->running = true;
	while (env->running)
	{
		commands = NULL;
		str = NULL;
		error = get_user_str(&str, env);
		if (error)
			return (error);
		tokens = get_tokens(str, env);
		if (tokens)
			commands = get_commands(env, tokens);
		if (commands)
		{
			exec_cmds(commands, env);
			ft_idllst_clear(&commands->list, free_command);
		}
	}
	rl_clear_history();
	return (SUCCESS);
}
