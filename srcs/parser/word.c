/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/22 11:42:53 by jberredj         ###   ########.fr       */
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
			&& !is_separator(line[len]) && line[len] != '\\'))
		len++;
	return (len);
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
	word = ft_calloc(sizeof(char), (len + 1));
	if (!word)
		return (0);
	if (is_quote(line[0]))
	{
		if (word)
			free(word);
		return (0);
	}
	while (line[*i] && !ft_isspace(line[*i]) && !is_quote(line[*i])
		&& !is_separator(line[*i]))
	{
		word[j] = line[*i];
		(*i)++;
		j++;
	}
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = word; //FAIRE FREE 
	return (0);
}
