/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:28:00 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/29 22:19:12 by jberredj         ###   ########.fr       */
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
/*
** REMOVE HEADER
*/
#include "_debug.h"

static char	*prompt_pwd(t_env_var *pwd, t_env_var *home)
{
	char	*pwd_str;
	char	*home_str;
	char	*prompt_pwd;
	size_t	home_lenght;

	pwd_str = pwd->value;
	home_str = home->value;
	home_lenght = ft_strlen(home_str);
	if (ft_strncmp(home_str, pwd_str, home_lenght) == 0)
		prompt_pwd = ft_strjoin("~", pwd_str + home_lenght);
	else
		prompt_pwd = ft_strdup(pwd->value);
	return (prompt_pwd);
}

static char	*get_prompt(t_env *env)
{
	char	*pwd;
	char	*user;
	char	*tmp_prompt;
	char	*prompt;

	pwd = prompt_pwd(env->pwd, env->home);
	tmp_prompt = ft_strjoin(
			"\033[1;32mMiddle Ages shell\033[0;0m:\033[1;34m",
			pwd);
	free(pwd);
	user = getenv("USER");
	if (ft_strncmp(user, "root", 5) == 0)
		prompt = ft_strjoin(tmp_prompt, "\033[0;31m#\033[0;0m ");
	else
		prompt = ft_strjoin(tmp_prompt, "\033[0;0m$ ");
	free(tmp_prompt);
	return (prompt);
}

void	exec_builtins(t_command *commands)
{
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(0);
	stdout_copy = dup(1);

}

void	exec_cmds(t_command *commands)
{
	int		exit_code;
	pid_t	child;

	while (commands)
	{
		if (commands->builtin)
			exec_builtins(commands);
		else
		{
			child = fork();
			if (child == 0)
			{
				if (commands->fd_in != 0)
				{
					dup2(commands->fd_in, 0);
					close(commands->fd_in);
				}
				if (commands->fd_out != 1)
				{
					dup2(commands->fd_out, 1);
					close(commands->fd_out);
				}
				execve(commands->path_to_cmd, commands->argv, commands->envp);
			}
			else
			{
				if (commands->fd_in != 0)
					close(commands->fd_in);
				if (commands->fd_out != 1)
					close(commands->fd_out);
				waitpid(child, &exit_code, 0);
			}
		}
		commands = ft_idllst_next_content(&commands->list);
	}
}

void	prompt(t_sh_dat *sh_dat)
{
	char		*prompt_str;
	char		*str;
	bool		running;
	t_command	*commands;
	pid_t		child;
	int			child_exit;

	running = true;
	child = 0;
	while (running)
	{
		prompt_str = get_prompt(&sh_dat->env);
		str = readline(prompt_str);
		free(prompt_str);
		if (str)
		{
			if (*str)
			{
				add_history(str);
				if (ft_strncmp(str, "exit", 4) == 0)
				{
					running = false;
					rl_clear_history();
					continue ;
				}
				t_token *tok;
				tok = tokenise_line(str);
				print_token(tok);
				commands = generate_commands_from_tokens(&sh_dat->env, tok);
				print_commands(commands);
				ft_idllst_clear(&tok->list, free_token);
				exec_cmds(commands);
				ft_idllst_clear(&commands->list, free_command);
				waitpid(child, &child_exit, 0);
				printf("Child exited\n");
			}
		}
		else
		{
			write(1, "exit\n", 5);
			running = false;
		}
		free(str);
	}
}
