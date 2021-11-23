/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:28:58 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/23 16:20:33 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISER_H
# define TOKENISER_H
# include "minishell.h"
# include "structs/t_token.h"
# include "../libft/includes/libft.h"
# include <stdbool.h>

t_token	*tokenise_line(char *line);
t_token	*new_token_add(t_token **tokens);
bool	is_quote(char c);
int		is_separator(char c);
int		search_quote(char *line, t_token **tokens, int *i, char quote);
int		search_word(char *line, t_token **tokens, int *i);
int		search_separator(char *line, t_token **tokens, int *i);
void	free_token(void *content);
#endif
