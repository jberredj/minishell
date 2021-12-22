/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:37:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 18:19:31 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "structs/t_token.h"
#include "structs/t_command.h"
#include "error_codes.h"
#include "../libft/includes/libft.h"
#include <signal.h>
#include "minish_signal.h"
#include <stdio.h>

int	heredoc_prompt(int fd, char *delimiter)
{
	char	*str;
	int		delimiter_found;

	str = (char *)1;
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
				write(fd, str, ft_strlen(str));
			}
			write(fd, "\n", 1);
			free(str);
		}
	}
	return (delimiter_found);
}

void	heredoc_ctrl_c(int sig, siginfo_t *info, void *ctx)
{
	(void)sig;
	(void)info;
	(void)ctx;
	close(0);
}

int	setup_hd_signal(int *fd)
{
	struct sigaction	sigint_act;

	*fd = dup(0);
	if (*fd == -1)
		return (FILE_ERROR);
	ft_bzero(&sigint_act, sizeof(struct sigaction));
	sigint_act.sa_sigaction = heredoc_ctrl_c;
	if (sigaction(SIGINT, &sigint_act, NULL) == -1)
		return (CREATE_ERROR);
	return (SUCCESS);
}

int	restore_signal(int fd)
{
	char				c;
	struct sigaction	sigint_act;
	int					err;

	ft_bzero(&sigint_act, sizeof(struct sigaction));
	sigint_act.sa_sigaction = ctrl_c;
	if (sigaction(SIGINT, &sigint_act, NULL) == -1)
		return (CREATE_ERROR);
	err = SUCCESS;
	if (read(0, &c, 0) == -1)
	{
		write(1, "\n", 1);
		err = CANCEL;
		if (dup2(fd, 0) == -1)
			err = FILE_ERROR;
	}
	close(fd);
	return (err);
}

int	heredoc(t_command *command, t_token **tokens)
{
	int		stdin_fd;
	int		fds[2];
	int		delimiter_found;
	int		error;

	*tokens = ft_idllst_next_content(&(*tokens)->list);
	if (pipe(fds))
		return (HERE_DOC_ERROR | PIPE_ERROR);
	error = setup_hd_signal(&stdin_fd);
	if (error)
		return (panic_hd_out(error, fds));
	delimiter_found = heredoc_prompt(fds[1], (*tokens)->content);
	close(fds[1]);
	if (command->fd_in != 0)
		close(command->fd_in);
	command->fd_in = fds[0];
	error = restore_signal(stdin_fd);
	if (error == CANCEL)
		return (HERE_DOC_ERROR | CANCEL);
	else if (error)
		return (error | HERE_DOC_ERROR);
	if (delimiter_found != 0)
		return (HERE_DOC_ERROR | UNFINISHED_LINE);
	return (SUCCESS);
}
