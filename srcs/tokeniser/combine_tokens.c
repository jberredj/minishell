/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:35:44 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/30 00:41:49 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "structs/t_token.h"
#include "error_codes.h"
#include "tokeniser.h"

int	create_str(char **str, t_token **tokens)
{
	char	*tmp;

	while (*tokens && (*tokens)->type != SEPARATOR)
	{
		dollar_case(*tokens);
		tmp = ft_strjoin((*tokens)->content, *str);
		free(*str);
		if (!tmp)
			return (ERR_MALLOC);
		*str = tmp;
		if ((*tokens)->had_a_space_before
			|| ft_idllst_is_head(&(*tokens)->list))
			break ;
		*tokens = ft_idllst_prev_content(&(*tokens)->list);
	}
	return (SUCCESS);
}

int	create_combined_token(t_token **tokens, t_token **new_list)
{
	char	*str;
	t_token	*new_token;

	str = ft_strdup((*tokens)->content);
	if (!str)
		return (ERR_MALLOC);
	*tokens = ft_idllst_prev_content(&(*tokens)->list);
	if (create_str(&str, tokens))
		return (ERR_MALLOC);
	remove_tokens_from_list(tokens);
	new_token = new_token_add_front(new_list);
	if (!new_token)
	{
		free(str);
		return (ERR_MALLOC);
	}
	new_token->content = str;
	new_token->type = WORD;
	return (0);
}

int	combine_tokens(t_token **tokens)
{
	t_token	*new_list;

	new_list = NULL;
	*tokens = ft_idllst_content(ft_idllst_get_tail(&(*tokens)->list));
	while (*tokens)
	{
		if (ft_idllst_is_head(&(*tokens)->list) || (*tokens)->type == SEPARATOR
			|| (*tokens)->had_a_space_before)
			add_current_token_to_new(tokens, &new_list);
		else
		{
			if (create_combined_token(tokens, &new_list))
			{
				if (new_list)
					ft_idllst_clear(&new_list->list, free_token);
				return (ERR_MALLOC);
			}
		}
	}
	*tokens = new_list;
	return (SUCCESS);
}
