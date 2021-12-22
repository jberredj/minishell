/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:26:49 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/21 17:38:16 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include "expander.h"
#include "env.h"
#include "tokeniser.h"
#include <stdio.h>
#include "_debug.h"
#include "error_codes.h"

char	*expanded_to_str(t_token *expanded)
{
	char	*expanded_str;

	expanded = ft_idllst_content(ft_idllst_get_head(&expanded->list));
	expanded_str = ft_strdup("");
	if (!expanded_str)
		return (NULL);
	while (expanded)
	{
		if (*expanded->content)
		{
			if (ft_gnljoin(&expanded_str, expanded->content))
			{
				free(expanded_str);
				return (NULL);
			}
		}
		expanded = ft_idllst_next_content(&expanded->list);
	}
	return (expanded_str);
}

int	substitute_var(t_env *env, char *dollar_pos, t_token **expanded_value)
{
	int			i;
	t_env_var	*existing;
	t_token		*last;

	while (dollar_pos)
	{
		dollar_pos++;
		i = 0;
		if (search_content(dollar_pos, &(*expanded_value), &i, get_var_len))
			return (ERR_MALLOC);
		last = ft_idllst_content(
				ft_idllst_get_tail(&(*expanded_value)->list));
		if (ft_strncmp(last->content, "?", 2) == 0)
		{
			if (exit_code_var(env, last))
				return (ERR_MALLOC);
		}
		else if (!*last->content)
		{
			if (dollar_alone(last))
				return (ERR_MALLOC);
		}
		else
		{
			existing = find_env_var_in_lst(env->env_vars,
					last->content);
			free(last->content);
			if (existing)
				last->content = ft_strdup(existing->value);
			else
				last->content = ft_strdup("");
			if (!last->content)
				return (ERR_MALLOC);
		}
		if (search_content(dollar_pos, &(*expanded_value), &i, get_words_len))
			return (ERR_MALLOC);
		dollar_pos = ft_strchr(dollar_pos, '$');
	}
	return (SUCCESS);
}

int	replace_token_content(t_token **to_free, t_token *tokens,
	t_token *expanded_value)
{
	char	*tmp;

	*to_free = NULL;
	tmp = expanded_to_str(expanded_value);
	if (!tmp)
		return (ERR_MALLOC);
	free(tokens->content);
	tokens->content = tmp;
	if (tokens->type != D_QUOTE && !*tokens->content)
			*to_free = ft_idllst_content(ft_idllst_pop(&tokens->list, NULL));
	ft_idllst_clear(&expanded_value->list, free_token);
	return (SUCCESS);
}
