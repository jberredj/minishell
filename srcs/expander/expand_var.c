/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dariadiakova <dariadiakova@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:07 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/02 22:13:42 by dariadiakov      ###   ########.fr       */
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

static int	get_var_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && ft_isalnum(line[len]))
		len++;
	return (len);
}

static char	*copy_var(char *line, int *i, int len)
{
	char	*var;
	int		j;

	var = ft_calloc(sizeof(char), (len + 1));
	if (!var)
		return (NULL);
	j = 0;
	while (line[*i] && ft_isalnum(line[*i]) && !ft_isspace(line[*i]))
	{
		var[j] = line[*i];
		(*i)++;
		j++;
	}
	return (var);
}

int	search_var(char *line, t_token **tokens, int *i)
{
	int			len;
	t_token		*new;
	char		*var;
	int			j;
	t_token		*next;

	j = 0;
	new = NULL;
	var = NULL;
	len = get_var_len(&line[*i]);
	var = copy_var(line, i, len);
	if (!var)
		return (-1);
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = var;
	next = ft_idllst_next_content(&(*tokens)->list);
	if (next)
		*tokens = next;
	return (0);
}

static int	get_content_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && (line[len] != '$'))
		len++;
	return (len);
}

static char	*copy_content(char *line, int *i, int len)
{
	char	*content;
	int		j;

	content = ft_calloc(sizeof(char), (len + 1));
	if (!content)
		return (NULL);
	j = 0;
	while (line[*i] && (line[*i] != '$'))
	{
		content[j] = line[*i];
		(*i)++;
		j++;
	}
	return (content);
}

int	search_content(char *line, t_token **tokens, int *i)
{
	int			len;
	t_token		*new;
	char		*content;
	int			j;
	t_token		*next;

	j = 0;
	new = NULL;
	content = NULL;
	len = get_content_len(&line[*i]);
	content = copy_content(line, i, len);
	if (!content)
		return (-1);
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = content;
	next = ft_idllst_next_content(&(*tokens)->list);
	if (next)
		*tokens = next;
	return (0);
}

char    *expanded_to_str(t_token *expanded)
{
	char    *expanded_str;
	
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

void    expand_var(t_token *tokens, t_env *env)
{
	t_env_var   *existing;
	char        *dollar_pos;
	int         i;
	t_token     *expanded_value;
	t_token		*to_free;
	
	to_free = NULL;
	while (tokens)
	{
		expanded_value = NULL;
		dollar_pos = NULL;
		if (ft_strncmp(tokens->content,"<<", 2) == 0)
			tokens = ft_idllst_next_content(&tokens->list);
		else if (tokens->type != S_QUOTE)
			dollar_pos = ft_strchr(tokens->content, '$');
		if (dollar_pos && dollar_pos != tokens->content)
			search_content(tokens->content, &expanded_value, &i);
		while (dollar_pos)
		{
			dollar_pos++;
			i = 0;
			search_var(dollar_pos, &expanded_value, &i);
			existing = find_env_var_in_lst(env->env_vars, expanded_value->content);
			free(expanded_value->content);
			if (existing)
				expanded_value->content = ft_strdup(existing->value);
			else
				expanded_value->content = ft_strdup("");
			search_content(dollar_pos, &expanded_value, &i);
			dollar_pos = ft_strchr(dollar_pos, '$');
		}
		if (expanded_value)
		{
			free(tokens->content);
			tokens->content = expanded_to_str(expanded_value);
			if (tokens->type != D_QUOTE && !*tokens->content)
				to_free = ft_idllst_content(ft_idllst_pop(&tokens->list, NULL));
			ft_idllst_clear(&expanded_value->list, free_token);
		}
		tokens = ft_idllst_next_content(&tokens->list);
		if (to_free)
			free_token(&to_free->list);
		to_free = NULL;
	}
}