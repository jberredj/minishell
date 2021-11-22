/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/22 17:57:32 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "../libft/includes/libft.h"
#include "env.h"
#include "minishell.h"
#include "tokeniser.h"

void	print_motd(void)
{
	printf("\033[0;32m|\\/| .  _  .  _ |_   _ | |\033[0;0m");
	printf(" Version : " VERSION_NUMBER);
	printf("\n");
	printf("\033[0;32m|  | | | | | _) | | (- | |\033[0;0m");
	printf(" Authors : ddiakova & jberredj\n");
#ifdef DEBUG
	printf("\033[1;33m/!\\ WARNING THIS A DEBUG BUILD, PERFORMANCE MAY BE BAD, OR EVERYTHING CAN JUST COLLASPE ON ITSELF OUT OF NOWHERE /!\\\033[0;0m\n");
#endif
}

char	*prompt_pwd(t_env_var *pwd, t_env_var *home)
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

char	*get_prompt(t_env *env)
{
	char	*pwd;
	char	*user;
	char	*tmp_prompt;
	char	*prompt;

	pwd = prompt_pwd(env->pwd, env->home);
	tmp_prompt = ft_strjoin(
			"\033[1;32mAnticshell\033[0;0m:\033[1;34m",
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

void	pseudo_env(char **envp)
{
	while (*envp)
	{
		ft_putendl_fd(*envp, 1);
		envp++;
	}
}

void	print_token(t_token *token)
{
	while (token)
	{
		printf("current token: %s\ntype : %d\n", token->content, token->type);
		token = ft_idllst_next_content(&token->list);
	}
}

typedef	struct s_command
{
	char		*path_to_cmd;
	int			argc;	
	char		**argv;
	char		**envp;
	t_idllist	list;
}				t_command;

char	*try_get_from_path(t_env_var *path, char *content)
{
	char	**split;
	size_t	len;
	size_t	i;
	char	*try_path;

	split = ft_split(path->value, ':');
	len = ft_split_size(split);
	i = -1;
	while (split[++i])
	{
		try_path = ft_strjoin(split[i], "/");
		ft_gnljoin(&try_path, content);
		if (access(try_path, X_OK) == 0)
			break ;
		free(try_path);
		try_path = NULL;
	}
	ft_free_split(split, len);
	return (try_path);
}

char	*try_relative_access(char *content)
{
	if (access(content, X_OK))
		return (ft_strdup(content));
	return (NULL);
}

char	*get_cmd_path(t_env_var *path, t_token cmd_tok)
{
	char	*cmd;

	if (ft_strncmp(cmd_tok.content, "./", 2) == 0
		|| ft_strncmp(cmd_tok.content, "../", 3) == 0)
		cmd = try_relative_access(cmd_tok.content);
	else
		cmd = try_get_from_path(path, cmd_tok.content);
	return (cmd);
}

t_command	*new_command_add(t_command *command)
{
	t_command	*new;

	new = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!new)
		return (NULL); // CHANGE TO MALLOC ERROR CODE
	new->list = ft_idllst_init(&new->list, new);
	if (!command)
		return (new);
	else
		ft_idllst_add_back(&new->list, &command->list);
	return (new);
}

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

char	**copy_envp(char **envp, int nbr)
{
	char	**copy;
	int		i;

	copy = (char **)ft_calloc(nbr + 1, sizeof(char *));
	i = -1;
	while(envp[++i])
		copy[i] = ft_strdup(envp[i]);
	return (copy);
}
t_command *generate_commands_from_tokens(t_env *env, t_token *tokens)
{
	t_command	*commands;
	bool		new_command;

	commands = NULL;
	new_command = true;
	while(tokens)
	{
		if (new_command)
		{
			commands = new_command_add(commands);
			commands->path_to_cmd = get_cmd_path(env->path, *tokens);
			add_to_command_argv(commands, commands->path_to_cmd);
			commands->envp = copy_envp(env->envp, env->nbr_exported);
			new_command = false;
		}
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

void	print_commands(t_command *commands)
{
	int	i;

	while (commands)
	{
		printf("command : %s \nargv : [", commands->path_to_cmd);
		i = -1;
		while (commands->argv[++i])
			printf("\"%s\", ", commands->argv[i]);
		printf("NULL]\n");
		commands = ft_idllst_next_content(&commands->list);
	}
}

void	free_token(void *content)
{
	t_token	*token;


	token = ft_idllst_content(content);
	if (token)
	{
		if (token->content)
			free(token->content);
		free(token);
	}
}

void	free_command(void *content)
{
	t_command	*command;
	int			i;

	command = ft_idllst_content(content);
	if (command)
	{
		if (command->argv)
		{
			i = -1;
			while (command->argv[++i])
				free(command->argv[i]);
			free(command->argv);
		}
		if (command->envp)
		{
			i = -1;
			while (command->envp[++i])
				free(command->envp[i]);
			free(command->envp);
		}
		free(command);
	}
}

void prompt(t_sh_dat *sh_dat)
{
	char		**split;
	char		*prompt_str;
	char		*str;
	bool		running;
	t_command	*commands;
	pid_t		child;
	int			child_exit;

	running = true;
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
				tok = tokenise_line(sh_dat, str);
				print_token(tok);
				commands = generate_commands_from_tokens(&sh_dat->env, tok);
				print_commands(commands);
				ft_idllst_clear(&tok->list, free_token);
				child = fork();
				if (child == 0)
				{
					free(str);
					free(sh_dat->env.envp);
					ft_idllst_clear(&sh_dat->env.env_vars->list, free_env_var);
					if (commands->path_to_cmd)
						execve(commands->path_to_cmd, commands->argv, commands->envp);
					ft_idllst_clear(&commands->list, free_command);
					printf("FAILED EXECUTION\n");
					exit(1);
				}
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

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sigquit_act;
	t_sh_dat			sh_dat;

	(void)argc;
	(void)argv;
	ft_bzero(&sigquit_act, sizeof(struct sigaction));
	sigquit_act.sa_sigaction = NULL;
	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
	ft_bzero(&sh_dat, sizeof(t_sh_dat));
	parse_herited_envp(&sh_dat.env, envp);
	print_motd();
	prompt(&sh_dat);
	free(sh_dat.env.envp);
	ft_idllst_clear(&sh_dat.env.env_vars->list, free_env_var);
	return (0);
}
