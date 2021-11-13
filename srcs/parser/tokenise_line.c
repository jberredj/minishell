/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:21:55 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/13 19:26:29 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include <stdbool.h>

bool	is_quote(char c)
{
	return ((bool)(c == '\'' || c == '\"'));
}

int	new_token(t_token **tokens)
{
	t_token *new;
	t_token	*tmp;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (1); // CHANGE TO MALLOC ERROR CODE
	tmp = *tokens;
	if (!tmp)
		*tokens = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int	search_word(char *line, t_token **tokens)
{
	int	i;

	if (is_quote(line[0]))
		return (0);
	while (!ft_isspace(line[i]) && !is_quote(line[i] && line[i])
	{
		
	}
	
}

int	search_separator(char *line, t_token **tokens)
{
	
}

int	search_s_quote(char *line, t_token **tokens)
{
	
}

int	search_d_quote(char *line, t_token **tokens)
{
	
}

int	search_backslash(char *line, t_token **tokens)
{
	
}

t_token	*tokenise_line(t_sh_dat *shdat, char *line)
{
	t_token	*tokens;
	int		i;

	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (search_word(line, &tokens))
			return (NULL); // handle error fallback
	}
	return (tokens);
}
