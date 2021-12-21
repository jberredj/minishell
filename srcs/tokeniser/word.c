/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/21 12:04:37 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include "error_codes.h"
#include "tokeniser.h"

static int	first_white_space(char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_isspace(line[len]))
		len++;
	return (len);
}

static int	select_how_many_to_copy(char *line, int quotes_nbr,
		int before_quotes, int len)
{
	if (quotes_nbr == 1)
		if (before_quotes != len)
			return (first_white_space(line));
	if (quotes_nbr == 2)
		if (before_quotes != 0)
			return (before_quotes);
	return (len);
}

static int	get_word_len(char *line)
{
	int		len;
	int		before_quotes;
	int		quotes_nbr;
	char	quote;

	len = 0;
	before_quotes = 0;
	quotes_nbr = 0;
	quote = '\0';
	while (line[len] && (!ft_isspace(line[len]) || quotes_nbr)
		&& !is_separator(line[len]) && quotes_nbr < 2)
	{
		if (is_quote(line[len]))
		{
			if (quotes_nbr == 0)
			{
				quote = line[len];
				before_quotes = len;
			}
			if (line[len] == quote)
				quotes_nbr++;
		}
		len++;
	}
	return (select_how_many_to_copy(line, quotes_nbr, before_quotes, len));
}

static char	*copy_word(char *line, int *i, int len)
{
	char	*word;
	int		j;

	word = ft_calloc(sizeof(char), (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	ft_memcpy(word, &line[*i], len);
	(*i) += len;
	return (word);
}

int	search_word(char *line, t_token **tokens, int *i)
{
	int			len;
	t_token		*new;
	char		*word;
	int			j;

	j = 0;
	new = NULL;
	word = NULL;
	while (ft_isspace(line[*i]))
		(*i)++;
	len = get_word_len(&line[*i]);
	if (len == 0)
		return (SUCCESS);
	word = copy_word(line, i, len);
	if (!word)
		return (ERR_MALLOC);
	new = new_token_add(tokens);
	if (new == NULL)
	{
		free(word);
		return (ERR_MALLOC);
	}
	new->content = word;
	new->type = WORD;
	return (SUCCESS);
}
