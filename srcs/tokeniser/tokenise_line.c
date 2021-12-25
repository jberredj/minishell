/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:21:55 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 21:24:16 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../libft/includes/libft.h"
#include "structs/t_token.h"
#include "tokeniser.h"
#include "error_codes.h"

t_token	*new_token_add(t_token **tokens)
{
	t_token	*new;

	if (!tokens)
		return (NULL);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->list = ft_idllst_init(&new->list, new);
	if (!*tokens)
		*tokens = new;
	else
		ft_idllst_add_back(&new->list, &(*tokens)->list);
	return (new);
}

int	panic_exit_tokeniser(t_token *tokens)
{
	ft_idllst_clear(&tokens->list, free_token);
	ft_putendl_fd("minishell: tokeniser: fatal error: malloc() failed", 2);
	return (ERR_MALLOC);
}

int	tokenise_line(t_token **tokens, char *line)
{
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (search_content(line, tokens, &i, get_word_len))
			return (panic_exit_tokeniser(*tokens));
		if (search_content(line, tokens, &i, get_sep_len))
			return (panic_exit_tokeniser(*tokens));
		if (!check_separator(tokens))
			if (check_for_quotes(tokens))
				return (panic_exit_tokeniser(*tokens));
	}
	return (SUCCESS);
}
