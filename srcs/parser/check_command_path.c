/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:03:12 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 14:21:13 by jberredj         ###   ########.fr       */
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
	if (!try_path)
		return (NULL);
	if (ft_gnljoin(&try_path, cmd))
	{
		free(try_path);
		return (NULL);
	}
	return (try_path);
}

static int	panic_get_path_out(char *try_path, char **split, size_t len)
{
	free(try_path);
	ft_free_split(split, len);
	return (ERR_MALLOC);
}

void	wrong_try(char **try_path_ptr)
{
	free(*try_path_ptr);
	*try_path_ptr = NULL;
}

static int	try_get_from_path(char **to_edit, t_env_var *path, char *content)
{
	char	**split;
	size_t	len;
	size_t	i;
	char	*try_path;

	split = ft_split(path->value, ':');
	if (!split)
		return (ERR_MALLOC);
	len = ft_split_size(split);
	i = -1;
	while (split[++i])
	{
		try_path = make_try_path(split[i], content);
		if (!try_path)
			return (panic_get_path_out(try_path, split, len));
		if (access(try_path, F_OK) == 0)
			i = len - 1;
		else
			wrong_try(&try_path);
	}
	ft_free_split(split, len);
	*to_edit = try_path;
	if (!try_path)
		return (NOT_EXIST);
	return (SUCCESS);
}

int	get_cmd_path(char **to_update, t_env_var *path, t_token cmd_tok)
{
	char	*command_path;
	int		is_a_path;
	int		error;

	command_path = NULL;
	is_a_path = !ft_strncmp(cmd_tok.content, "/", 1);
	if (!is_a_path && path)
		error = try_get_from_path(&command_path, path, cmd_tok.content);
	if (!path || is_a_path || error == NOT_EXIST)
	{
		command_path = ft_strdup(cmd_tok.content);
		if (!command_path)
			return (ERR_MALLOC);
		error = SUCCESS;
	}
	*to_update = command_path;
	return (error);
}
