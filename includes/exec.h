/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:59:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 21:45:01 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "structs/t_env.h"
# include "structs/t_command.h"

int		exec_cmds(t_command *commands, t_env *env);
int		exec_builtins(t_command *commands, t_env *env);
int		exec_external(t_command *commands, t_env *env);
/*
** Executers Utils
*/
void	clean_all_exec(t_command *commands, t_env *env);
void	close_unused_fds(t_command *command);
int		swap_std_with_fds(t_command *command);
/*
** Main executer error
*/
void	kill_launched_commands(t_command *commands);
int		panic_exec_out(int error, t_command *commands, t_env *env);
/*
** External commands errors
*/
int		print_exec_error(char *path, bool had_env_path);
int		panic_child_out(int error, t_command *command);
/*
** Builtin commands errors
*/
int		panic_builtin_out(int error, t_command *command);
/*
** File redirection
*/
int		treat_redirection(t_command *command);
int		create_pipe(t_command *command);
int		infile_redirect(t_command *command);
int		outfile_redirect(t_command *command);
#endif