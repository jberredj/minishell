/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:21:55 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 14:33:51 by jberredj         ###   ########.fr       */
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

t_token	*new_token_add(t_token **tokens)
{
	t_token	*new;

	if (!tokens)
		return (NULL);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL); // CHANGE TO MALLOC ERROR CODE
	*new->list = ft_idllst_init(&new->list, new);
	if (!*tokens)
		*tokens = new;
	else
		ft_idllst_add_back(&new->list, &(*tokens)->list);
	return (new);
}

int	search_word(char *line, t_token **tokens)
{
	int		i;
	t_token	*new;

	if (is_quote(line[0]))
		return (0);
	while (!ft_isspace(line[i]) && !is_quote(line[i]) && line[i])
	{
		new = new_token(tokens);
		if (new == NULL)
			return (1);
		new->content = ft_strdup(line[i]); //FAIRE FREE 
		i++;
	}
	return (0);
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

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (search_word(line, &tokens))
			return (NULL); // handle error fallback
		if (search_separator(line, &tokens))
			return (NULL);
		if (search_s_quote(line, &tokens))
			return (NULL);
		if (search_d_quote(line, &tokens))
			return (NULL);
		if (search_backslash(line, &tokens))
			return (NULL);
		i++;
	}
	return (tokens);
}
