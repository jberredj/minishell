/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:18:04 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/04 18:25:10 by jberredj         ###   ########.fr       */
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

bool	need_to_create(char *str)
{
	while (*str && !ft_isspace(*str))
		str++;
	if (!*str)
		return (false);
	return (true);
}

size_t	basic_word_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

void	secure_token_remove(t_token **tokens, t_token **copy_tokens)
{
	t_token	*to_set;
	size_t	size;
	bool	is_head;

	to_set = NULL;
	is_head = ft_idllst_is_head(&(*tokens)->list);
	size = ft_idllst_size(&(*tokens)->list);
	if (is_head && size == 1)
		to_set = NULL;
	else if (is_head)
		to_set = ft_idllst_next_content(&(*tokens)->list);
	ft_idllst_del(&(*tokens)->list, free_token);
	*tokens = to_set;
	*copy_tokens = to_set;
}

int	new_subtoken(t_token **tokens, char *str, int *i)
{
	size_t	len;
	t_token	*subtoken;

	subtoken = new_token_add(tokens);
	if (!subtoken)
		return (ERR_MALLOC);
	len = basic_word_len(&str[*i]);
	subtoken->content = (char *)ft_calloc(len + 1, sizeof(char));
	if (!subtoken->content)
		return (ERR_MALLOC);
	ft_memcpy(subtoken->content, &str[*i], len);
	(*i) += len;
	subtoken->type = S_QUOTE;
	return (SUCCESS);
}

int	create_subtokens(t_token **tokens, t_token **copy_tokens)
{
	int		i;
	char	*str;
	int		error;

	str = (*tokens)->content;
	if (!need_to_create(str))
		return (SUCCESS);
	(*tokens)->content = NULL;
	secure_token_remove(tokens, copy_tokens);
	i = 0;
	error = SUCCESS;
	while (str[i] && !error)
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			error = new_subtoken(tokens, str, &i);
	}
	if (!*copy_tokens)
		*copy_tokens = *tokens;
	free(str);
	return (error);
}
