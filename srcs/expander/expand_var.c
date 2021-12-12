/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:07 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/07 19:06:48 by ddiakova         ###   ########.fr       */
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

char	*expanded_to_str(t_token *expanded)
{
	char	*expanded_str;

	expanded = ft_idllst_content(ft_idllst_get_head(&expanded->list));
	expanded_str = ft_strdup("");
	while (expanded)
	{
		if (*expanded->content)
			ft_gnljoin(&expanded_str, expanded->content);
		expanded = ft_idllst_next_content(&expanded->list);
	}
	return (expanded_str);
}

void	substitute_var(t_env *env, char *dollar_pos, t_token **expanded_value)
{
	int			i;
	t_env_var	*existing;

	while (dollar_pos)
	{
		dollar_pos++;
		i = 0;
		search_var(dollar_pos, &(*expanded_value), &i);
		if (ft_strncmp((*expanded_value)->content, "?", 2) == 0)
			exit_code_var(env, *expanded_value);
		else if (!*(*expanded_value)->content)
			dollar_alone(*expanded_value);
		else
		{
			existing = find_env_var_in_lst(env->env_vars,
					(*expanded_value)->content);
			free((*expanded_value)->content);
			if (existing)
				(*expanded_value)->content = ft_strdup(existing->value);
			else
				(*expanded_value)->content = ft_strdup("");
		}
		search_content(dollar_pos, &(*expanded_value), &i);
		dollar_pos = ft_strchr(dollar_pos, '$');
	}
}

t_token	*replace_token_content(t_token *tokens, t_token *expanded_value)
{
	t_token		*to_free;

	to_free = NULL;
	free(tokens->content);
	tokens->content = expanded_to_str(expanded_value);
	if (tokens->type != D_QUOTE && !*tokens->content)
			to_free = ft_idllst_content(ft_idllst_pop(&tokens->list, NULL));
	ft_idllst_clear(&expanded_value->list, free_token);
	return (to_free);
}

void	expand_var(t_token *tokens, t_env *env)
{
	int			i;
	char		*dollar_pos;
	t_token		*expanded_value;
	t_token		*to_free;

	to_free = NULL;
	while (tokens)
	{
		expanded_value = NULL;
		dollar_pos = NULL;
		if (ft_strncmp(tokens->content, "<<", 2) == 0)
			tokens = ft_idllst_next_content(&tokens->list);
		else if (tokens->type != S_QUOTE)
			dollar_pos = ft_strchr(tokens->content, '$');
		if (dollar_pos && dollar_pos != tokens->content)
			search_content(tokens->content, &expanded_value, &i);
		substitute_var(env, dollar_pos, &expanded_value);
		if (expanded_value)
			to_free = replace_token_content(tokens, expanded_value);
		tokens = ft_idllst_next_content(&tokens->list);
		if (to_free)
			free_token(&to_free->list);
		to_free = NULL;
	}
}
