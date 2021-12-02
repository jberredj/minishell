/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:53:25 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 19:05:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "structs/t_token.h"
#include "structs/t_command.h"
#include "structs/t_env.h"
#include "tokeniser.h"
#include "../libft/includes/ft_idllst.h"
#include "parser.h"
#include "error_codes.h"

int	create_pipe(t_env *env, t_command **command, t_token *tokens,
	int *new_command)
{
	int		fds[2];
	t_token	*next;

	next = ft_idllst_next_content(&tokens->list);
	if ((next && next->type == SEPARATOR)
		|| ft_idllst_is_head(&tokens->list) || ft_idllst_is_tail(&tokens->list))
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
