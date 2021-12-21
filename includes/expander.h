/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/21 14:55:32 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "structs/t_env.h"
# include "structs/t_token.h"
# include "../libft/includes/ft_idllst.h"

void	expand_var(t_token *tokens, t_env *env);
int		get_words_len(char *line, bool min_val);
int		get_var_len(char *line, bool min_val);
int		search_var(char *line, t_token **tokens, int *i);
void	exit_code_var(t_env *env, t_token *expanded_value);
void	dollar_alone(t_token *expanded_value);

#endif