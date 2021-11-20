/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:21:55 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/20 19:59:03 by ddiakova         ###   ########.fr       */
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

static int	is_separator(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((ft_strchr("|<>;&()", line[i])))
			return (1);
		i++;
	}
	return (0);
}

t_token	*new_token_add(t_token **tokens)
{
	t_token	*new;

	if (!tokens)
		return (NULL);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL); // CHANGE TO MALLOC ERROR CODE
	new->list = ft_idllst_init(&new->list, new);
	if (!*tokens)
		*tokens = new;
	else
		ft_idllst_add_back(&new->list, &(*tokens)->list);
	return (new);
}

static int	get_word_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_isspace(line[len] && !is_quote(line[len])
			&& !is_separator(&line[len]) && line[len] != '\\'))
		len++;
	return (len);
}

static int	get_sep_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_isspace(line[len]) && line[len] != is_separator(&line[len]))
		len++;
	return (len);
}

static int	search_word(char *line, t_token **tokens, int *i)
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
		&& !is_separator(&line[*i]))
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


static int	search_separator(char *line, t_token **tokens, int *i)
{
	int			len;
	t_token		*new;
	char		*sep;
	int			j;

	j = 0;
	new = NULL;
	sep = NULL;
	while (ft_isspace(line[*i]))
		(*i)++;
	len = get_sep_len(&line[*i]);
	sep = ft_calloc(sizeof(char), (len + 1));
	if (!sep)
		return (0);
	if (is_quote(line[0]))
	{
		if (sep)
			free(sep);
		return (0);
	}
	while (line[*i] && !ft_isspace(line[*i]) && !is_quote(line[*i])
		&& is_separator(&line[*i]))
	{
		sep[j] = line[*i];
		(*i)++;
		j++;
	}
	(*i)++;
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = sep;
	return (0);
}

static int	get_quote_len(char *line, char quote)
{
	int	len;

	if (*line != quote)
		return (-1);
	len = 0;
	(line)++;
	while (line[len] && (line[len]) != quote)
		len++;
	if (line[len] == '\0')
		return (-2);
	return (len);
}

static int	search_quote(char *line, t_token **tokens, int *i, char quote)
{
	int			j;
	int			len;
	t_token		*new;
	char		*squote;

	j = 0;
	new = NULL;
	squote = NULL;
	while (ft_isspace(line[*i]))
		(*i)++;
	len = get_quote_len(&line[*i], quote);
	if (len < 0)
		return (len);
	(*i)++;
	// printf ("%d\n", len);
	squote = ft_calloc(sizeof(char), (len + 1));
	if (!squote)
		return (0);
	while (line[*i] && (line[*i]) != quote)
	{
		squote[j] = line[*i];
		(*i)++;
		j++;
	}
	(*i)++;
	new = new_token_add(tokens);
	if (new == NULL)
		return (1);
	new->content = squote;
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
		if (search_word(line, &tokens, &i))
			return (NULL);
		if (search_separator(line, &tokens, &i))
			return (NULL);
		if (search_quote(line, &tokens, &i, '\'') < -1)
			i++;
		if (search_quote(line, &tokens, &i, '\"') < -1)
			i++;
		// if (search_backslash(line, &tokens))
		// 	return (NULL);
		if (ft_isspace(line[i]))
			i++;
	}
	return (tokens);
}
