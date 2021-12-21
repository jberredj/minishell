/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:21:55 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/21 11:56:53 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
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

t_token	*panic_exit_tokeniser(t_token *tokens)
{
	ft_idllst_clear(&tokens->list, free_token);
	ft_putendl_fd("minishell: tokeniser: fatal error: malloc() failed", 2);
	return (NULL);
}

t_token	*tokenise_line(char *line)
{
	t_token	*tokens;
	int		error;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (search_word(line, &tokens, &i))
			return (panic_exit_tokeniser(tokens));
		if (search_separator(line, &tokens, &i))
			return (panic_exit_tokeniser(tokens));
		if (check_for_quotes(&tokens))
			return (panic_exit_tokeniser(tokens));
		if (ft_isspace(line[i]))
			i++;
	}
	return (tokens);
}
