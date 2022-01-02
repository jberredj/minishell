/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/02 14:28:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "structs/t_env.h"
# include "structs/t_token.h"
# include "../libft/includes/ft_idllst.h"

int		expand_var(t_token **tokens, t_env *env);
int		get_words_len(char *line, bool min_val);
int		get_var_len(char *line, bool min_val);
int		exit_code_var(t_env *env, t_token *expanded_value);
int		dollar_alone(t_token *expanded_value);
int		substitute_var(t_env *env, char *dollar_pos, t_token **expanded_value);
int		replace_token_content(t_token **to_free, t_token **tokens,
			t_token *expanded_value, t_token **copy_tokens);
int		create_subtokens(t_token **tokens, t_token **copy_tokens);
void	secure_token_remove(t_token **tokens, t_token **copy_tokens);
#endif