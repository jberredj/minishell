/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:15:41 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 19:57:00 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "../libft/includes/ft_string.h"

char	*get_prompt(t_env *env)
{
	const char	*tmp_prompt = "\033[1;32mminishell\033[0;0m";
	char		*prompt;

	if (env->exit_code == 0)
		prompt = ft_strjoin(tmp_prompt, "\033[0;0m> ");
	else
		prompt = ft_strjoin(tmp_prompt, "\033[0;31m>\033[0m ");
	return (prompt);
}
