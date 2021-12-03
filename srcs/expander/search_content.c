/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:06:26 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/03 12:18:08 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include "expander.h"
#include "env.h"
#include "tokeniser.h"
#include "_debug.h"

static int	get_content_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && (line[len] != '$'))
		len++;
	return (len);
}

static char	*copy_content(char *line, int *i, int len)
{
	char	*content;
	int		j;

	content = ft_calloc(sizeof(char), (len + 1));
	if (!content)
		return (NULL);
	j = 0;
	while (line[*i] && (line[*i] != '$'))
	{
		content[j] = line[*i];
		(*i)++;
		j++;
	}
	return (content);
}

int	search_content(char *line, t_token **tokens, int *i)
{
	int			len;
	t_token		*new;
	char		*content;
	int			j;
	t_token		*next;

	j = 0;
	new = NULL;
	content = NULL;
	len = get_content_len(&line[*i]);
	content = copy_content(line, i, len);
	if (!content)
		return (-1);
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = content;
	next = ft_idllst_next_content(&(*tokens)->list);
	if (next)
		*tokens = next;
	return (0);
}
