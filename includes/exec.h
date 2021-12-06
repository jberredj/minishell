/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:59:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/06 14:42:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "structs/t_env.h"
# include "structs/t_command.h"

void	exec_cmds(t_command *commands, t_env *env);
void	exec_builtins(t_command *commands, t_env *env);
void	exec_external(t_command *commands, t_env *env);
/*
** Executers Utils
*/
void	clean_all_exec(t_command *commands, t_env *env);
void	closed_unused_fds(t_command *command);
void	swap_std_with_fds(t_command *command);
#endif