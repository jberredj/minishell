/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:03:12 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 16:48:32 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include "env.h"

static char	*try_get_from_path(t_env_var *path, char *content)
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
	if (access(content, X_OK) == 0)
		return (ft_strdup(content));
	return (NULL);
}

char	*get_cmd_path(t_env_var *path, t_token cmd_tok)
{
	char	*cmd;

	if (ft_strncmp(cmd_tok.content, "/", 1) == 0
		|| ft_strncmp(cmd_tok.content, "./", 2) == 0
		|| ft_strncmp(cmd_tok.content, "../", 3) == 0)
		cmd = try_relative_access(cmd_tok.content);
	else
		cmd = try_get_from_path(path, cmd_tok.content);
	return (cmd);
}
