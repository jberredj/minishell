/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:02:18 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/29 22:21:56 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../libft/includes/libft.h"
#include "structs/t_token.h"
#include "tokeniser.h"
#include "error_codes.h"

bool	is_quote(char c)
{
	return ((bool)(c == '\'' || c == '\"'));
}

static int	prepare_replacement(t_token **replacement_token,
	size_t len, int type, bool space_before)
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
	(*replacement_token)->had_a_space_before = space_before;
	(*replacement_token)->type = type;
	return (SUCCESS);
}

void	replace_token(t_token **tokens, t_token *last_token,
	t_token *replacement_token)
{
	bool	is_head;

	is_head = ft_idllst_is_head(&last_token->list);
	ft_idllst_pop(&last_token->list, free_token);
	if (is_head)
		*tokens = replacement_token;
	else
		ft_idllst_add_back(&replacement_token->list, &(*tokens)->list);
}

int	check_for_quotes(t_token **tokens, char *user_str, bool first)
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
	if (first || !ft_isspace(*(user_str - len - 1)))
		last_token->had_a_space_before = false;
	if (!(len > 1 && is_quote(line[0])
			&& is_quote(line[len - 1])))
		return (SUCCESS);
	if (prepare_replacement(&replacement_token, len - 2, (int)line[0],
			last_token->had_a_space_before))
		return (ERR_MALLOC);
	ft_memcpy(replacement_token->content, line + 1, len - 2);
	replace_token(tokens, last_token, replacement_token);
	return (SUCCESS);
}
