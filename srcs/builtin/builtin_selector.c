/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_selector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:26:23 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/29 19:19:12 by jberredj         ###   ########.fr       */
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
	if (ft_strncmp(cmd_tok.content, "echo", 4) == 0)
		commands->builtin = echo;
	else if (ft_strncmp(cmd_tok.content, "cd", 2) == 0)
		commands->builtin = builtin_placeholder;
	else if (ft_strncmp(cmd_tok.content, "pwd", 3) == 0)
		commands->builtin = builtin_placeholder;
	else if (ft_strncmp(cmd_tok.content, "export", 6) == 0)
		commands->builtin = builtin_placeholder;
	else if (ft_strncmp(cmd_tok.content, "unset", 5) == 0)
		commands->builtin = builtin_placeholder;
	else if (ft_strncmp(cmd_tok.content, "env", 3) == 0)
		commands->builtin = builtin_placeholder;
	else if (ft_strncmp(cmd_tok.content, "exit", 4) == 0)
		commands->builtin = builtin_placeholder;
	else
		error = get_cmd_path(&commands->path_to_cmd, path, cmd_tok);
	return (error);
}
