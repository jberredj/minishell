/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:37:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/01 09:41:16 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_token.h"
#include "structs/t_command.h"
#include "error_codes.h"
#include "../libft/includes/libft.h"

int	heredoc_prompt()
{

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
