/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:00:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 12:49:33 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define CMD 1
# define REDIRECT 2
# include "structs/t_env.h"
# include "structs/t_token.h"
# include "structs/t_command.h"

int			get_cmd_path(char **to_update, t_env_var *path, t_token cmd_tok);
t_command	*new_command_add(t_command *command);
int			add_to_command_argv(t_command *cmd, char *content);
int			generate_commands_from_tokens(t_env *env, t_token *tokens,
				t_command **commands);
void		free_command(void *content);
int			heredoc(t_command *command, t_token **tokens);
int			parse_pipe(t_command **command, t_token *tokens,
				int *new_command);
t_command	*init_new_command(t_command *commands);
int			parse_infile_redirect(t_command *command, t_token **tokens);
int			parse_outfile_redirect(t_command *command, t_token **tokens,
				int mode);
void		free_xv(char **xv);
int			print_error_pars(int error, t_token *tokens);
t_command	*cancel_commands(t_command *commands);
int			panic_hd_out(int error, int fds[2]);
#endif