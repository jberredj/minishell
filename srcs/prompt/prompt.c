/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:28:00 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/01 15:26:07 by jberredj         ###   ########.fr       */
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
#include "minishell.h"
#include "exec.h"
/*
** REMOVE HEADER
*/
#include "_debug.h"

char	*prompt_cwd(t_env_var *pwd)
{
	char	*cwd;

	if (pwd)
		return (ft_strdup(pwd->value));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("."));
	return (cwd);
}

char	*get_home_str(t_env_var *home)
{
	if (!home)
		return (NULL);
	return (home->value);
}

static char	*prompt_pwd(t_env_var *pwd, t_env_var *home)
{
	char	*cwd;
	char	*home_str;
	char	*prompt_pwd;
	size_t	home_lenght;

	cwd = prompt_cwd(pwd);
	home_str = get_home_str(home);
	if (home_str)
	{
		home_lenght = ft_strlen(home_str);
		if (ft_strncmp(home_str, cwd, home_lenght) == 0)
			prompt_pwd = ft_strjoin("~", cwd + home_lenght);
		else
			prompt_pwd = ft_strdup(cwd);
	}
	else
		prompt_pwd = ft_strdup(cwd);
	free(cwd);
	return (prompt_pwd);
}

static char	*get_prompt(t_env *env)
{
	char	*pwd;
	char	*tmp_prompt;
	char	*prompt;

	pwd = prompt_pwd(env->pwd, env->home);
	tmp_prompt = ft_strjoin(
			"\033[1;32mMiddle Ages shell\033[0;0m:\033[1;34m",
			pwd);
	free(pwd);
	if (env->exit_code == 0)
		prompt = ft_strjoin(tmp_prompt, "\033[0;0m> ");
	else
		prompt = ft_strjoin(tmp_prompt, "\033[0;31m>\033[0m ");
	free(tmp_prompt);
	return (prompt);
}

void	prompt(t_env *env)
{
	char		*prompt_str;
	char		*str;
	t_command	*commands;

	env->running = true;
	while (env->running)
	{
		prompt_str = get_prompt(env);
		str = readline(prompt_str);
		free(prompt_str);
		if (str)
		{
			if (*str)
			{
				add_history(str);
				t_token *tok;
				tok = tokenise_line(str);
				commands = generate_commands_from_tokens(env, tok);
				// print_commands(commands);
				ft_idllst_clear(&tok->list, free_token);
				exec_cmds(commands, env);
				ft_idllst_clear(&commands->list, free_command);
				// printf("Child exited\n");
			}
		}
		else
		{
			write(1, "exit\n", 5);
			env->running = false;
		}
		free(str);
	}
	rl_clear_history();
}
