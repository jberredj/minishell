/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:25:12 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/04 18:41:40 by jberredj         ###   ########.fr       */
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

int	implemented_sep(char *line)
{
	if (ft_strncmp(line, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(line, "<", 1) == 0)
		return (1);
	if (ft_strncmp(line, ">", 1) == 0)
		return (1);
	if (ft_strncmp(line, "|", 1) == 0)
		return (1);
	return (0);
}

int	get_sep_len(char *line, bool min_val)
{
	int	len;

	if (min_val)
		return (1);
	len = implemented_sep(line);
	if (len)
		return (len);
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
