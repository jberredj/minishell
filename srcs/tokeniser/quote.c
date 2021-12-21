/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:02:18 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/21 11:50:27 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include "tokeniser.h"
#include "error_codes.h"

bool	is_quote(char c)
{
	return ((bool)(c == '\'' || c == '\"'));
}

static int	prepare_replacement(t_token **replacement_token,
	size_t len, int type)
{
	*replacement_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!replacement_token)
		return (ERR_MALLOC);
	(*replacement_token)->list = ft_idllst_init(&(*replacement_token)->list,
			*replacement_token);
	(*replacement_token)->content = ft_calloc(len + 1, sizeof(char));
	if (!(*replacement_token)->content)
	{
		free_token(&(*replacement_token)->list);
		return (ERR_MALLOC);
	}
	(*replacement_token)->type = type;
	return (SUCCESS);
}

int	check_for_quotes(t_token **tokens)
{
	t_token	*last_token;
	char	*line;
	t_token	*replacement_token;
	size_t	len;

	last_token = ft_idllst_content(ft_idllst_get_tail(&(*tokens)->list));
	if (last_token->type != WORD)
		return (SUCCESS);
	line = last_token->content;
	len = ft_strlen(line);
	if (!(len > 1 && is_quote(line[0])
			&& is_quote(line[len - 1])))
		return (SUCCESS);
	if (prepare_replacement(&replacement_token, len - 2, (int)line[0]))
		return (ERR_MALLOC);
	ft_memcpy(replacement_token->content, line + 1, len - 2);
	if (!*tokens)
		*tokens = replacement_token;
	else
	{
		ft_idllst_pop(&last_token->list, free_token);
		ft_idllst_add_back(&replacement_token->list, &(*tokens)->list);
	}
	return (SUCCESS);
}
