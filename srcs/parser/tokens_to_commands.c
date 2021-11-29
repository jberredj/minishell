/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:21:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/29 22:10:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CMD 1
#define REDIRECT 2

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


static t_command	*init_new_command(t_env *env, t_command *commands)
{
	commands = new_command_add(commands);
	commands->envp = copy_envp(env->envp, env->nbr_exported);
	commands->fd_in = 0;
	commands->fd_out = 1;
	return (commands);
}

int	create_pipe(t_env *env, t_command **command, t_token *tokens, int *new_command)
{
	int	fds[2];

	if (ft_idllst_is_head(&tokens->list) || ft_idllst_is_tail(&tokens->list))
		return (SYNTAX_ERROR | PIPE_ERROR);
	if (pipe(fds))
		return (CREATE_ERROR | PIPE_ERROR);
	if ((*command)->fd_out == 1)
		(*command)->fd_out = fds[1];
	else
		close(fds[1]);
	(*command) = init_new_command(env, *command);
	(*command)->fd_in = fds[0];
	*new_command = 0;
	return (SUCCESS);
}

int	infile_redirect(t_command *command, t_token **tokens)
{
	int	fd;

	*tokens = ft_idllst_next_content(&(*tokens)->list);
	if (access((*tokens)->content, F_OK) == 0)
	{
		if (access((*tokens)->content, R_OK) == 0)
		{
			fd = open((*tokens)->content, O_RDONLY);
			if (fd == -1)
				return (OPEN_ERROR | R_ERROR);
			if (command->fd_in != 0)
				close(command->fd_in);
			command->fd_in = fd;
			return (SUCCESS);
		}
		return (R_ERROR | FILE_ERROR);
	}
	return (NOT_EXIST_ERROR | FILE_ERROR);
	
}

int	outfile_redirect(t_command *command, t_token **tokens, int mode)
{
	int	fd;

	*tokens = ft_idllst_next_content(&(*tokens)->list);
	fd = open((*tokens)->content, O_CREAT | O_WRONLY | mode, 0644);
	if (fd == -1)
		return (CREATE_ERROR | FILE_ERROR);
	if (command->fd_out != 0)
		close(command->fd_out);
	command->fd_out = fd;
	return (SUCCESS);
}

int	heredoc(t_command *command, t_token **tokens)
{
	int		fds[2];
	int		delimiter_found;
	char	*delimiter;
	char	*str;

	*tokens = ft_idllst_next_content(&(*tokens)->list);
	if (pipe(fds))
		return (CREATE_ERROR | PIPE_ERROR);
	delimiter = (*tokens)->content;
	str = ft_strdup("");
	delimiter_found = 1;
	while (str && delimiter_found != 0)
	{
		str = readline("> ");
		if (str)
		{
			if (*str)
			{
				delimiter_found = ft_strncmp(str, delimiter, ft_strlen(str));
				if (delimiter_found == 0)
				{
					free(str);
					continue ;
				}
				write(fds[1], str, ft_strlen(str));
			}
			write(fds[1], "\n", 1);
			free(str);
		}
	}
	close(fds[1]);
	if (command->fd_in != 0)
		close(command->fd_in);
	command->fd_in = fds[0];
	if (delimiter_found != 0)
		return (HERE_DOC_ERROR | UNFINISHED_LINE_ERROR);
	return (SUCCESS);
}

int	treat_separator(t_env *env, t_token **tokens, t_command **command, int *new_command)
{
	if (ft_strncmp((*tokens)->content, "<", ft_strlen((*tokens)->content)) == 0)
		return (infile_redirect(*command, tokens));
	if (ft_strncmp((*tokens)->content, "<<", ft_strlen((*tokens)->content)) == 0)
		heredoc(*command, tokens);
	if (ft_strncmp((*tokens)->content, ">", ft_strlen((*tokens)->content)) == 0)
		outfile_redirect(*command, tokens, O_TRUNC);
	if (ft_strncmp((*tokens)->content, ">>", ft_strlen((*tokens)->content)) == 0)
		outfile_redirect(*command, tokens, O_APPEND);
	if (ft_strncmp((*tokens)->content, "|", ft_strlen((*tokens)->content)) == 0)
		return (create_pipe(env, command, *tokens, new_command));
	return (UNKNOW_TOKEN);
}

void	fill_error(int error, t_token *token, t_command *command)
{
	(void)error;
	(void)token;
	if (command->error)
		free(command->error);
	command->error = ft_strdup("CPT\n");
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
			treat_separator(env, &tokens, &commands, &new_command);
		else
		{
			if (new_command != CMD)
			{
				error = check_builtin(commands, env->path, *tokens);
				new_command = CMD;
			}
			add_to_command_argv(commands, tokens->content);
		}
		if (error)
			fill_error(error, tokens, commands);
		tokens = ft_idllst_next_content(&tokens->list);
	}
	return (ft_idllst_content(ft_idllst_get_head(&commands->list)));
}

