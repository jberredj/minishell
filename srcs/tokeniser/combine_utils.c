/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 00:06:44 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/30 00:43:24 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "structs/t_token.h"
#include "error_codes.h"
#include "tokeniser.h"

void	add_current_token_to_new(t_token **token, t_token **new_list)
{
	t_token	*to_copy;
	t_token	*to_assign;
	size_t	size;

	to_copy = *token;
	size = ft_idllst_size(&to_copy->list);
	if (size == 1)
		to_assign = NULL;
	else
		to_assign = ft_idllst_prev_content(&(*token)->list);
	ft_idllst_pop(&(*token)->list, NULL);
	to_copy->list = ft_idllst_init(&to_copy->list, to_copy);
	*token = to_assign;
	if (*new_list)
		ft_idllst_add_front(&to_copy->list, &(*new_list)->list);
	*new_list = to_copy;
}

void	remove_tokens_from_list(t_token **tokens)
{
	bool	is_first;

	is_first = ft_idllst_is_head(&(*tokens)->list);
	if (!is_first && (*tokens)->type != SEPARATOR)
		*tokens = ft_idllst_prev_content(&(*tokens)->list);
	ft_idllst_clear_after(&(*tokens)->list, free_token, false);
	if (is_first)
	{
		ft_idllst_del(&(*tokens)->list, free_token);
		(*tokens) = NULL;
	}
}

t_token	*new_token_add_front(t_token **tokens)
{
	t_token	*new;

	if (!tokens)
		return (NULL);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->list = ft_idllst_init(&new->list, new);
	if (*tokens)
		ft_idllst_add_front(&new->list, &(*tokens)->list);
	*tokens = new;
	return (new);
}

void	dollar_case(t_token *token)
{
	size_t	len;

	if (token->type != WORD)
		return ;
	len = ft_strlen(token->content);
	if (token->content[len - 1] == '$')
		token->content[len - 1] = '\0';
}
