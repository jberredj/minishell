/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:07 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/02 14:33:36 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/includes/libft.h"
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "error_codes.h"
#include "expander.h"
#include "tokeniser.h"

int	panic_expand_var(t_token *tokens, t_token *expanded_value)
{
	if (tokens)
		ft_idllst_clear(&tokens->list, free_token);
	if (expanded_value)
		ft_idllst_clear(&expanded_value->list, free_token);
	ft_putendl_fd("minishell: expander: fatal error: malloc() failed", 2);
	return (ERR_MALLOC);
}

void	try_get_next(t_token **tokens)
{
	if (*tokens)
		*tokens = ft_idllst_next_content(&(*tokens)->list);
}

void	secure_to_free(t_token *to_free,
	t_token **tokens, t_token **copy_tokens)
{
	bool	is_head;

	is_head = ft_idllst_is_head(&(*tokens)->list);
	if (is_head && to_free == *tokens)
	{
		secure_token_remove(tokens, copy_tokens);
	}
	else if (to_free)
		free_token(&to_free->list);
	try_get_next(tokens);
}

int	expand_all_tokens(t_token **tokens,
	t_token **copy_tokens, int *i, t_env *env)
{
	char		*dollar_pos;
	t_token		*expanded_value;
	t_token		*to_free;

	to_free = NULL;
	expanded_value = NULL;
	dollar_pos = NULL;
	if (ft_strncmp((*tokens)->content, "<<", 2) == 0)
		*tokens = ft_idllst_next_content(&(*tokens)->list);
	else if ((*tokens)->type != S_QUOTE)
		dollar_pos = ft_strchr((*tokens)->content, '$');
	if (dollar_pos && dollar_pos != (*tokens)->content)
		if (search_content((*tokens)->content, &expanded_value,
				i, get_words_len) == ERR_MALLOC)
			return (panic_expand_var((*tokens), expanded_value));
	if (substitute_var(env, dollar_pos, &expanded_value))
		return (panic_expand_var((*tokens), expanded_value));
	if (expanded_value)
		if (replace_token_content(&to_free, tokens, expanded_value,
				copy_tokens))
			return (panic_expand_var((*tokens), expanded_value));
	secure_to_free(to_free, tokens, copy_tokens);
	to_free = NULL;
	return (SUCCESS);
}

int	expand_var(t_token **tokens, t_env *env)
{
	t_token	*copy_tokens;
	int		i;

	i = 0;
	copy_tokens = *tokens;
	while (*tokens)
	{
		if (expand_all_tokens(tokens, &copy_tokens, &i, env))
			return (ERR_MALLOC);
	}
	*tokens = copy_tokens;
	return (SUCCESS);
}
