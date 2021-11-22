/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:25:12 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/22 15:17:46 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include "tokeniser.h"

int	is_separator(char c)
{
	if ((ft_strchr("|<>;&()", c)))
		return (1);
	return (0);
}

static int	get_sep_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_isspace(line[len]) && is_separator(line[len]))
		len++;
	return (len);
}

int	search_separator(char *line, t_token **tokens, int *i)
{
	int			len;
	t_token		*new;
	char		*sep;
	int			j;

	j = 0;
	new = NULL;
	sep = NULL;
	while (ft_isspace(line[*i]))
		(*i)++;
	len = get_sep_len(&line[*i]);
	if (len < 1)
		return (len);
	printf ("%d\n", len);
	sep = ft_calloc(sizeof(char), (len + 1));
	if (!sep)
		return (0);
	if (is_quote(line[0]))
	{
		if (sep)
			free(sep);
		return (0);
	}
	while (line[*i] && !ft_isalnum(line[*i]) && !ft_isspace(line[*i]) 
		&& !is_quote(line[*i]) && is_separator(line[*i]))
	{
		sep[j] = line[*i];
		(*i)++;
		j++;
	}
	// (*i)++;
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = sep;
	new->type = SEPARATOR;
	return (0);
}
