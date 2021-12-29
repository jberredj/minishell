/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:25:12 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/29 23:02:55 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../libft/includes/libft.h"
#include "structs/t_token.h"
#include "tokeniser.h"
#include "error_codes.h"

int	is_separator(char c)
{
	if ((ft_strchr("|<>;&()", c)))
		return (1);
	return (0);
}

int	get_sep_len(char *line, bool min_val)
{
	int	len;

	if (min_val)
		return (1);
	len = 0;
	while (line[len] && !ft_isspace(line[len]) && is_separator(line[len]))
		len++;
	return (len);
}

bool	check_separator(t_token **tokens)
{
	bool	sep;
	t_token	*last_token;
	char	*line;

	last_token = ft_idllst_content(ft_idllst_get_tail(&(*tokens)->list));
	line = last_token->content;
	sep = false;
	if (!is_separator(*line))
		return (false);
	while (*line)
		if (is_separator(*line++))
			sep = true;
	if (sep)
		last_token->type = SEPARATOR;
	return (sep);
}
