/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:23:20 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/23 16:42:06 by jberredj         ###   ########.fr       */
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

static char	*copy_quote_content(char *line, int *i, char quote, int len)
{
	char	*quote_content;
	int		j;

	j = 0;
	(*i)++;
	quote_content = ft_calloc(sizeof(char), (len + 1));
	if (!quote_content)
		return (NULL);
	while (line[*i] && (line[*i]) != quote)
	{
		quote_content[j] = line[*i];
		(*i)++;
		j++;
	}
	(*i)++;
	return (quote_content);
}

int	search_quote(char *line, t_token **tokens, int *i, char quote)
{
	int			j;
	int			len;
	t_token		*new;
	char		*quote_content;

	j = 0;
	new = NULL;
	quote_content = NULL;
	while (ft_isspace(line[*i]))
		(*i)++;
	len = get_quote_len(&line[*i], quote);
	if (len < 0)
		return (len);
	quote_content = copy_quote_content(line, i, quote, len);
	if (!quote_content)
		return (-1);
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = quote_content;
	new->type = quote;
	return (0);
}
