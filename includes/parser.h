/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:00:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 16:20:12 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "structs/t_env.h"
# include "structs/t_token.h"
# include "structs/t_command.h"

char		*get_cmd_path(t_env_var *path, t_token cmd_tok);
t_command	*new_command_add(t_command *command);
void		add_to_command_argv(t_command *cmd, char *content);
t_command	*generate_commands_from_tokens(t_env *env, t_token *tokens);
void		free_command(void *content);
#endif