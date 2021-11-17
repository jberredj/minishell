/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:21:55 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 21:41:35 by ddiakova         ###   ########.fr       */
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

int	get_word_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_isspace(line[len] && !is_quote(line[len])
			&& !is_separator(line[len])))
		len++;
	return (len);
}

int	search_word(char *line, t_token **tokens)
{
	int			i;
	int			len;
	t_token		*new;
	char		*word;

	i = 0;
	new = NULL;
	word = NULL;
	len = get_word_len(line);
	word = ft_calloc(sizeof(char), (len + 1));
	if (!word)
		return (0);
	if (is_quote(line[0]))
		return (0);
	while (!ft_isspace(line[i]) && !is_quote(line[i])
		&& !is_separator(line[i]) && line[i])
	{
		word[i] = line[i];
		i++;
	}
	new = new_token(tokens);
	if (new == NULL)
		return (1);
	new->content = ft_strdup(word); //FAIRE FREE 
	if (new->content == NULL)
		return (1);
	if (word)
		free (word);
	return (0);
}

int	is_separator(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(ft_strchr("|<>;&()", line[i])))
			return (1);
		i++;
	}
	return (0);
}

int	search_separator(char *line, t_token **tokens)
{
	int			i;
	t_token		*new;

	i = 0;
	new = NULL;
	while (line[i])
	{
		if (is_separator(line))
		{
			new = new_token(tokens);
			new->content = ft_strdup(line[i]);
		}
		i++;
	}
	return (0);
}

int	search_s_quote(char *line, t_token **tokens)
{
	int			i;
	t_token		*new;

	i = 0;
	new = NULL;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			new = new_token(tokens);
			new->content = ft_strdup("\'");
		}
		i++;
	}
	return (0);
}

int	search_d_quote(char *line, t_token **tokens)
{
	int			i;
	t_token		*new;

	i = 0;
	new = NULL;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			new = new_token(tokens);
			new->content = ft_strdup("\"");
		}
		i++;
	}
	return (0);
}

int	search_backslash(char *line, t_token **tokens)
{
	int			i;
	t_token		*new;

	i = 0;
	new = NULL;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			new = new_token(tokens);
			new->content = ft_strdup("\\");
		}
		i++;
	}
	return (0);
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
