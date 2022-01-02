/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:26:49 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/02 14:29:32 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../libft/includes/libft.h"
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "env.h"
#include "tokeniser.h"
#include "expander.h"
#include "error_codes.h"

static char	*expanded_to_str(t_token *expanded)
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

int	check_special_case(t_token *last, t_env *env)
{
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
		return (SUCCESS);
	return (2);
}

int	check_normal_case(t_token *last, t_env *env)
{
	t_env_var	*existing;

	existing = find_env_var_in_lst(env->env_vars,
			last->content);
	free(last->content);
	if (existing)
		last->content = ft_strdup(existing->value);
	else
		last->content = ft_strdup("");
	if (!last->content)
		return (ERR_MALLOC);
	return (SUCCESS);
}

int	substitute_var(t_env *env, char *dollar_pos, t_token **expanded_value)
{
	int			i;
	t_token		*last;
	int			error;

	while (dollar_pos)
	{
		dollar_pos++;
		i = 0;
		if (search_content(dollar_pos, &(*expanded_value), &i, get_var_len)
			== ERR_MALLOC)
			return (ERR_MALLOC);
		last = ft_idllst_content(
				ft_idllst_get_tail(&(*expanded_value)->list));
		error = check_special_case(last, env);
		if (error == ERR_MALLOC)
			return (ERR_MALLOC);
		else if (!error)
			if (check_normal_case(last, env))
				return (ERR_MALLOC);
		if (search_content(dollar_pos, &(*expanded_value), &i, get_words_len)
			== ERR_MALLOC)
			return (ERR_MALLOC);
		dollar_pos = ft_strchr(dollar_pos, '$');
	}
	return (SUCCESS);
}

int	replace_token_content(t_token **to_free, t_token **tokens,
	t_token *expanded_value, t_token **copy_tokens)
{
	char	*tmp;

	*to_free = NULL;
	tmp = expanded_to_str(expanded_value);
	if (!tmp)
		return (ERR_MALLOC);
	free((*tokens)->content);
	(*tokens)->content = tmp;
	if (!*(*tokens)->content && !ft_idllst_is_tail(&(*tokens)->list))
		((t_token *)((*tokens)->list.next->struct_addr))->had_a_space_before
			= true;
	if ((*tokens)->type != D_QUOTE && !*(*tokens)->content)
			*to_free = ft_idllst_content(ft_idllst_pop(&(*tokens)->list, NULL));
	ft_idllst_clear(&expanded_value->list, free_token);
	if ((*tokens)->type == WORD)
		return (create_subtokens(tokens, copy_tokens));
	return (SUCCESS);
}
