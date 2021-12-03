/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:15:41 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/03 14:45:37 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "../libft/includes/ft_string.h"

static char	*prompt_cwd(t_env_var *pwd)
{
	char	*cwd;

	if (pwd)
		return (ft_strdup(pwd->value));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("."));
	return (cwd);
}

static char	*get_home_str(t_env_var *home)
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

char	*get_prompt(t_env *env)
{
	char	*pwd;
	char	*tmp_prompt;
	char	*prompt;

	pwd = prompt_pwd(env->pwd, env->home);
	tmp_prompt = ft_strjoin(
			"\033[1;32mEarly Modern Period shell\033[0;0m:\033[1;34m",
			pwd);
	free(pwd);
	if (env->exit_code == 0)
		prompt = ft_strjoin(tmp_prompt, "\033[0;0m> ");
	else
		prompt = ft_strjoin(tmp_prompt, "\033[0;31m>\033[0m ");
	free(tmp_prompt);
	return (prompt);
}
