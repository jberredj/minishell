/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/29 22:38:49 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../libft/includes/libft.h"
#include "structs/t_token.h"
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

static int	find_len(char *line)
{
	int		len;
	int		before_quotes;
	int		quotes_nbr;
	char	quote;

	len = -1;
	before_quotes = 0;
	quotes_nbr = 0;
	quote = '\0';
	while (line[++len] && (!ft_isspace(line[len]) || quotes_nbr)
		&& (!is_separator(line[len]) || quotes_nbr) && quotes_nbr < 2)
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
	}
	return (select_how_many_to_copy(line, quotes_nbr, before_quotes, len));
}

int	get_word_len(char *line, bool min_val)
{
	if (min_val)
		return (1);
	return (find_len(line));
}
