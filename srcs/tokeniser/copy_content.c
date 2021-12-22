/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:46:20 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/21 17:15:36 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>
#include "error_codes.h"
#include "tokeniser.h"

static char	*copy_content(char *line, int *i, int len)
{
	char	*content;

	content = ft_calloc(sizeof(char), (len + 1));
	if (!content)
		return (NULL);
	ft_memcpy(content, &line[*i], len);
	(*i) += len;
	return (content);
}

int	search_content(char *line, t_token **tokens, int *i,
	int (*len_func)(char*, bool))
{
	int			len;
	t_token		*new;
	char		*content;
	int			j;

	j = 0;
	new = NULL;
	content = NULL;
	len = len_func(&line[*i], false);
	if (len < len_func(NULL, true))
		return (SUCCESS);
	content = copy_content(line, i, len);
	if (!content)
		return (ERR_MALLOC);
	new = new_token_add(tokens);
	if (new == NULL)
	{
		free(content);
		return (ERR_MALLOC);
	}
	new->content = content;
	new->type = WORD;
	return (SUCCESS);
}
