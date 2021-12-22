/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:21:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 13:17:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "structs/t_command.h"
#include "structs/t_token.h"
#include "structs/t_env.h"
#include "../libft/includes/libft.h"
#include "builtin.h"
#include "env.h"
#include "parser.h"
#include "error_codes.h"

t_command	*init_new_command(t_env *env, t_command *commands)
{
	commands = new_command_add(commands);
	commands->fd_in = 0;
	commands->fd_out = 1;
	return (commands);
}

int	treat_separator(t_env *env, t_token **tokens, t_command **command,
	int *new_command)
{
	if (ft_strncmp((*tokens)->content, "<", ft_strlen((*tokens)->content)) == 0)
		return (parse_infile_redirect(*command, tokens));
	if (ft_strncmp((*tokens)->content, "<<",
			ft_strlen((*tokens)->content)) == 0)
		return (heredoc(*command, tokens));
	if (ft_strncmp((*tokens)->content, ">", ft_strlen((*tokens)->content)) == 0)
		return (parse_outfile_redirect(*command, tokens, O_TRUNC));
	if (ft_strncmp((*tokens)->content, ">>",
			ft_strlen((*tokens)->content)) == 0)
		return (parse_outfile_redirect(*command, tokens, O_APPEND));
	if (ft_strncmp((*tokens)->content, "|", ft_strlen((*tokens)->content)) == 0)
		return (parse_pipe(env, command, *tokens, new_command));
	return (UNKNOW_TOKEN);
}

t_command	*cancel_commands(t_command *commands)
{
	ft_idllst_clear(&commands->list, free_command);
	return (NULL);
}

int	print_error_pars(int error, t_token *tokens)
{
	if (error & HERE_DOC_ERROR)
	{
		if (error & CREATE_ERROR)
			perror("minishell: cannot create pipes for here-document");
		if (error & UNFINISHED_LINE_ERROR)
		{
			ft_putstr_fd("- minishell: warning : here-document delimited\
 by end-of-file (wanted \"", 2);
			ft_putstr_fd(tokens->content, 2);
			ft_putendl_fd("\")", 2);
		}
	}
	return (0);
}

t_command	*generate_commands_from_tokens(t_env *env, t_token *tokens)
{
	t_command	*commands;
	int			new_command;
	int			error;

	commands = NULL;
	commands = init_new_command(env, commands);
	new_command = 0;
	while (tokens)
	{	
		if (tokens->type == SEPARATOR)
			error = treat_separator(env, &tokens, &commands, &new_command);
		else
		{
			if (new_command != CMD)
			{
				error = check_builtin(commands, env->path, *tokens);
				new_command = CMD;
			}
			add_to_command_argv(commands, tokens->content);
		}
		if (error & CANCEL)
			return (cancel_commands(commands));
		else if (error)
			print_error_pars(error, tokens);
		tokens = ft_idllst_next_content(&tokens->list);
	}
	return (ft_idllst_content(ft_idllst_get_head(&commands->list)));
}
