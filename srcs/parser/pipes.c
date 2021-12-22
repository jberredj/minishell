/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:53:25 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 16:33:54 by jberredj         ###   ########.fr       */
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

int	parse_pipe(t_env *env, t_command **command, t_token *tokens,
	int *new_command)
{
	t_token	*next;

	next = ft_idllst_next_content(&tokens->list);
	if (ft_idllst_is_head(&tokens->list) || ft_idllst_is_tail(&tokens->list))
		return (SYNTAX_ERROR | PIPE_ERROR);
	(*command)->piped = true;
	(*command) = init_new_command(env, *command);
	*new_command = 0;
	return (SUCCESS);
}
