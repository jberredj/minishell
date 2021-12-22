/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:59:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 11:05:42 by jberredj         ###   ########.fr       */
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
void	closed_unused_fds(t_command *command);
int		swap_std_with_fds(t_command *command);
/*
** Main executer error
*/
int		panic_exec_out(int error, t_command *commands, t_env *env);
/*
** External commands errors
*/
int		check_file(char *path);
int		print_exec_error(char *path, bool had_env_path);
char	*try_exec_command(t_command *command);
int		panic_child_out(int error, t_command *command);
/*
** Builtin commands errors
*/
char	*builtin_pointer_to_name(int (*builtin)(char**, t_env *));
int		panic_builtin_out(int error, t_command *command);
#endif