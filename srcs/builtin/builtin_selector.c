/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_selector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:26:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/12 17:21:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_command.h"
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "builtin.h"
#include "parser.h"
#include "error_codes.h"

int	check_builtin(t_command *commands, t_env_var *path,
				t_token cmd_tok)
{
	int	error;

	error = SUCCESS;
	if (ft_strncmp(cmd_tok.content, "echo", ft_strlen(cmd_tok.content)) == 0)
		commands->builtin = echo;
	else if (ft_strncmp(cmd_tok.content, "cd", ft_strlen(cmd_tok.content)) == 0)
		commands->builtin = cd;
	else if (ft_strncmp(cmd_tok.content, "pwd",
			ft_strlen(cmd_tok.content)) == 0)
		commands->builtin = pwd;
	else if (ft_strncmp(cmd_tok.content, "export",
			ft_strlen(cmd_tok.content)) == 0)
		commands->builtin = builtin_placeholder;
	else if (ft_strncmp(cmd_tok.content, "unset",
			ft_strlen(cmd_tok.content)) == 0)
		commands->builtin = builtin_placeholder;
	else if (ft_strncmp(cmd_tok.content, "env",
			ft_strlen(cmd_tok.content)) == 0)
		commands->builtin = env;
	else if (ft_strncmp(cmd_tok.content, "exit",
			ft_strlen(cmd_tok.content)) == 0)
		commands->builtin = minish_exit;
	else
		error = get_cmd_path(&commands->path_to_cmd, path, cmd_tok);
	if (error)
		commands->path_to_cmd = ft_strdup(cmd_tok.content);
	return (error);
}