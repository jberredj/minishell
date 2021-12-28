/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:50:54 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/28 23:50:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include "structs/t_env.h"
# include "structs/t_token.h"
# include "structs/t_command.h"

int			prompt(t_env *env);
char		*get_prompt(t_env *env);
t_token		*get_tokens(char *str, t_env *env);
t_command	*get_commands(t_env *env, t_token *tokens);
#endif