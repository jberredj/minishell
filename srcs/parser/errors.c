/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:53:16 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 18:20:27 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_codes.h"
#include "structs/t_token.h"
#include "structs/t_command.h"
#include "../libft/includes/libft.h"
#include "parser.h"
#include "unistd.h"
#include <stdio.h>

int	panic_hd_out(int error, int fds[2])
{
	int	i;

	i = -1;
	while (++i < 2)
		close(fds[i]);
	return (HERE_DOC_ERROR | error);
}

t_command	*cancel_commands(t_command *commands)
{
	ft_idllst_clear(&commands->list, free_command);
	return (NULL);
}

static int	here_docs_errors(int error, t_token *tokens)
{
	if (error & PIPE_ERROR)
	{
		perror("minishell: cannot create pipes for here-document");
		return (CANCEL);
	}
	if (error & UNFINISHED_LINE)
	{
		ft_putstr_fd("- minishell: warning : here-document delimited\
 by end-of-file (wanted \"", 2);
		ft_putstr_fd(tokens->content, 2);
		ft_putendl_fd("\")", 2);
		return (SUCCESS);
	}
	if (error & (CREATE_ERROR | FILE_ERROR))
	{
		if (error & CREATE_ERROR)
			perror("minishell: here-documents: fatal error:\
 sigaction() failed");
		if (error & FILE_ERROR)
			perror("minishell: here-documents: fatal error: dup() failed");
		return (FATAL_ERROR | CANCEL);
	}
	return (SUCCESS);
}

int	print_error_pars(int error, t_token *tokens)
{
	if (error & HERE_DOC_ERROR)
		return (here_docs_errors(error, tokens));
	if (error & (CHECK_BUILTIN | ERR_MALLOC) || error & ERR_MALLOC)
	{
		ft_putendl_fd("minishell: parser: fatal error: malloc() failed", 2);
		return (FATAL_ERROR | CANCEL);
	}
	if (error & (SYNTAX_ERROR | UNKNOW_TOKEN))
	{
		ft_putstr_fd("minishell: parser: syntax error near token \"", 2);
		ft_putstr_fd(tokens->content, 2);
		ft_putendl_fd("\"", 2);
		return (CANCEL);
	}
	return (SUCCESS);
}