/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/10 10:48:22 by jberredj         ###   ########.fr       */
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
	printf("\033[1;33m/!\\ WARNING THIS A DEBUG BUILD, PERFORMANCE MAY BE BAD /!\\\033[0;0m\n");
#endif
}

char	*get_prompt()
{
	char	*pwd;
	char	*user;
	char	*tmp_prompt;
	char	*prompt;

	pwd = getenv("PWD");
	tmp_prompt = ft_strjoin("\033[1;32mpre-historicshell\033[0;0m:\033[1;34m", pwd);
	user = getenv("USER");
	if (ft_strncmp(user, "root", 5) == 0)
		prompt = ft_strjoin(tmp_prompt, "\033[0;31m#\033[0;0m ");
	else
		prompt = ft_strjoin(tmp_prompt, "\033[0;0m$ ");
	free(tmp_prompt);
	return (prompt);
}

typedef struct s_sh_dat
{
	t_env	env;
}				t_sh_dat;

void prompt(t_sh_dat *sh_dat)
{
	t_env_var	*elem;
	char		*prompt_str;
	char		*str;
	bool		running;
	
	running = true;
	while (running)
	{
		prompt_str = get_prompt();
		str = readline(prompt_str);
		free(prompt_str);
		add_history(str);
		if (*str)
		{
			if (ft_strncmp(str, "exit", 4) == 0)
			{
				running = false;
				rl_clear_history();
				continue ;
			}
			else if (ft_strncmp(str, "unset", 4) == 0)
			{
				char **split;

				split = ft_split(str, ' ');
				pop_env_var(&sh_dat->env, split[1]);
				ft_free_split(split, ft_split_size(split));
				continue ;
			}
			elem = create_env_var_from_str(str, sh_dat->env.nbr_vars + 1);
			add_env_var(&sh_dat->env, elem);
		}
		free(str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	
	t_sh_dat	sh_dat;
	t_env_var	*test;

	ft_bzero(&sh_dat, sizeof(t_sh_dat));
	parse_herited_envp(&sh_dat.env, envp);
	print_motd();
	prompt(&sh_dat);
	ft_lstclear(&sh_dat.env.elems, free_env_var);
	return (0);
}
