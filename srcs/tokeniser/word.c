/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/02 16:01:11 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include "tokeniser.h"

static int	get_word_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_isspace(line[len] && !is_quote(line[len])
			&& !is_separator(line[len])))
		len++;
	return (len);
}

static char	*copy_word(char *line, int *i, int len)
{
	char	*word;
	int		j;

	word = ft_calloc(sizeof(char), (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (line[*i] && !ft_isspace(line[*i]) && !is_quote(line[*i])
		&& !is_separator(line[*i]))
	{
		word[j] = line[*i];
		(*i)++;
		j++;
	}
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
	word = copy_word(line, i, len);
	if (!word)
		return (-1);
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = word;
	new->type = WORD;
	return (0);
}
