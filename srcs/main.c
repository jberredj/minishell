/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 12:15:19 by jberredj         ###   ########.fr       */
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

typedef struct s_command
{
	uint16_t	flags;
	char		*command;
	char		**argv;
}				t_command;

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
			"\033[1;32mpre-historicshell\033[0;0m:\033[1;34m",
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

void	pseudo_env(t_env *env)
{
	t_env_var	*env_var_node;

	env_var_node = env->env_vars;
	while (env_var_node)
	{
		printf("%s=%s\n", env_var_node->name, env_var_node->value);
		env_var_node = ft_idllst_next_content(&env_var_node->list);
	}
}

void prompt(t_sh_dat *sh_dat)
{
	char		**split;
	t_env_var	*elem;
	char		*prompt_str;
	char		*str;
	bool		running;

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
				else if (ft_strncmp(str, "unset", 4) == 0)
				{
					split = ft_split(str, ' ');
					pop_env_var_from_env(&sh_dat->env, split[1]);
					ft_free_split(split, ft_split_size(split));
					continue ;
				}
				else if (ft_strncmp(str, "env", 3) == 0)
				{
					pseudo_env(&sh_dat->env);
					continue ;
				}
				elem = create_env_var_from_str(str, sh_dat->env.nbr_vars + 1);
				add_env_var(&sh_dat->env, elem);
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
	ft_idllst_clear(&sh_dat.env.env_vars->list, free_env_var);
	return (0);
}
