/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:28:58 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/30 00:43:11 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISER_H
# define TOKENISER_H
# include "minishell.h"
# include "structs/t_token.h"
# include "../libft/includes/libft.h"
# include <stdbool.h>

int		tokenise_line(t_token **tokens, char *line);
t_token	*new_token_add(t_token **tokens);
bool	is_quote(char c);
int		is_separator(char c);
int		search_content(char *line, t_token **tokens, int *i,
			int (*len_func)(char*, bool));
bool	check_separator(t_token **tokens);
void	free_token(void *content);
int		get_word_len(char *line, bool min_val);
int		get_sep_len(char *line, bool min_val);
int		check_for_quotes(t_token **tokens, char *user_str, bool first);
int		combine_tokens(t_token **tokens);
void	add_current_token_to_new(t_token **token, t_token **new_list);
void	remove_tokens_from_list(t_token **tokens);
t_token	*new_token_add_front(t_token **tokens);
void	dollar_case(t_token *token);
#endif
