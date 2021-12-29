/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:53:25 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/29 22:28:23 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/includes/ft_idllst.h"
#include "structs/t_token.h"
#include "structs/t_command.h"
#include "structs/t_env.h"
#include "tokeniser.h"
#include "parser.h"
#include "error_codes.h"

int	check_valid_next_separator(char	*sep)
{
	if (ft_strncmp(sep, "<", 2) == 0)
		return (SUCCESS);
	else if (ft_strncmp(sep, "<<", 3) == 0)
		return (SUCCESS);
	else if (ft_strncmp(sep, ">", 2) == 0)
		return (SUCCESS);
	else if (ft_strncmp(sep, ">>", 3) == 0)
		return (SUCCESS);
	return (SYNTAX_ERROR);
}

int	check_if_valid_command_after(t_token *tokens)
{
	int	type;

	type = 0;
	while (tokens)
	{
		if (tokens->type != SEPARATOR)
			return (SUCCESS);
		else
		{
			if (check_valid_next_separator(tokens->content))
				return (SYNTAX_ERROR);
			tokens = ft_idllst_next_content(&tokens->list);
		}
		if (tokens)
			tokens = ft_idllst_next_content(&tokens->list);
	}
	return (SYNTAX_ERROR | PIPE_ERROR);
}

int	parse_pipe(t_command **command, t_token *tokens,
	int *new_command)
{
	int	error;

	error = check_if_valid_command_after(ft_idllst_next_content(&tokens->list));
	if (error)
		return (error);
	if (ft_idllst_is_head(&tokens->list) || ft_idllst_is_tail(&tokens->list))
		return (SYNTAX_ERROR | PIPE_ERROR);
	(*command)->piped = true;
	(*command) = init_new_command(*command);
	*new_command = 0;
	return (SUCCESS);
}
