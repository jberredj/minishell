/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:23:20 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/21 15:47:37 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include "tokeniser.h"

bool	is_quote(char c)
{
	return ((bool)(c == '\'' || c == '\"'));
}

static int	get_quote_len(char *line, char quote)
{
	int	len;

	if (*line != quote)
		return (-1);
	len = 0;
	(line)++;
	while (line[len] && (line[len]) != quote)
		len++;
	if (line[len] == '\0')
		return (-2);
	return (len);
}

int	search_quote(char *line, t_token **tokens, int *i, char quote)
{
	int			j;
	int			len;
	t_token		*new;
	char		*squote;

	j = 0;
	new = NULL;
	squote = NULL;
	while (ft_isspace(line[*i]))
		(*i)++;
	len = get_quote_len(&line[*i], quote);
	if (len < 0)
		return (len);
	(*i)++;
	// printf ("%d\n", len);
	squote = ft_calloc(sizeof(char), (len + 1));
	if (!squote)
		return (0);
	while (line[*i] && (line[*i]) != quote)
	{
		squote[j] = line[*i];
		(*i)++;
		j++;
	}
	(*i)++;
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = squote;
	return (0);
}
