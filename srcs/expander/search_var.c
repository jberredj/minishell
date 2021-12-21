/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:00:01 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/21 12:05:27 by jberredj         ###   ########.fr       */
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

static int	get_var_len(char *line)
{
	int	len;

	len = 0;
	if (line[0] == '?' || ft_isdigit(line[0]))
		return (1);
	while (line[len] && (ft_isalnum(line[len]) || line[len] == '_'))
		len++;
	return (len);
}

static char	*copy_var(char *line, int *i, int len)
{
	char	*var;
	int		j;

	var = ft_calloc(sizeof(char), (len + 1));
	if (!var)
		return (NULL);
	j = 0;
	while (line[*i] && j < len)
	{
		var[j] = line[*i];
		(*i)++;
		j++;
	}
	return (var);
}

int	search_var(char *line, t_token **tokens, int *i)
{
	int			len;
	t_token		*new;
	char		*var;
	int			j;
	t_token		*next;

	j = 0;
	new = NULL;
	var = NULL;
	len = get_var_len(&line[*i]);
	var = copy_var(line, i, len);
	if (!var)
		return (-1);
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = var;
	next = ft_idllst_next_content(&(*tokens)->list);
	if (next)
		*tokens = next;
	return (0);
}
