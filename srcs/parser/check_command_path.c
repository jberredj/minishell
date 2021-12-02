/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:03:12 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 18:28:22 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include "env.h"
#include "error_codes.h"

static char	*make_try_path(char *base_path, char *cmd)
{
	char	*try_path;

	try_path = ft_strjoin(base_path, "/");
	ft_gnljoin(&try_path, cmd);
	return (try_path);
}

static int	error_wrong_rights(char *try_path, char **split, size_t len)
{
	free(try_path);
	ft_free_split(split, len);
	return (RIGHT_ERROR | X_ERROR | FILE_ERROR);
}

static int	try_get_from_path(char **to_edit, t_env_var *path, char *content)
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
		try_path = make_try_path(split[i], content);
		if (access(try_path, F_OK) == 0)
		{
			if (access(try_path, X_OK) == 0)
				break ;
			return (error_wrong_rights(try_path, split, len));
		}
		free(try_path);
		try_path = NULL;
	}
	ft_free_split(split, len);
	*to_edit = try_path;
	if (!try_path)
		return (NOT_EXIST_ERROR | FILE_ERROR);
	return (SUCCESS);
}

int	try_relative_access(char **to_edit, char *content)
{
	if (access(content, F_OK) == 0)
	{
		if (access(content, X_OK) == 0)
		{
			*to_edit = ft_strdup(content);
			return (SUCCESS);
		}
		return (RIGHT_ERROR | X_ERROR | FILE_ERROR);
	}
	return (NOT_EXIST_ERROR | FILE_ERROR);
}

int	get_cmd_path(char **to_update, t_env_var *path, t_token cmd_tok)
{
	char	*command_path;
	int		error;

	command_path = NULL;
	if (ft_strncmp(cmd_tok.content, "/", 1) == 0
		|| ft_strncmp(cmd_tok.content, "./", 2) == 0
		|| ft_strncmp(cmd_tok.content, "../", 3) == 0)
		error = try_relative_access(&command_path, cmd_tok.content);
	else
		error = try_get_from_path(&command_path, path, cmd_tok.content);
	*to_update = command_path;
	return (error);
}
