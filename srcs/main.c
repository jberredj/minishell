/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/04 16:26:41 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

typedef struct s_command
{
	uint16_t	flags;
	char		*command;
	char		**argv;
}				t_command;

#ifndef VERSION_NUMBER
# define VERSION_NUMBER "ALPHA 0.0"
#endif

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
	tmp_prompt = ft_strjoin("\033[1;32mminishell\033[0;0m:\033[1;34m", pwd);
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

void	prompt(void)
{
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	t_sh_dat	sh_dat;

	ft_bzero(&sh_dat, sizeof(t_sh_dat));
	parse_herited_envp(&sh_dat.env, envp);
	print_motd();
	prompt = get_prompt();
	readline(prompt);
	free(prompt);
	return (0);
}
