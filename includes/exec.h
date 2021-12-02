/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:59:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/01 11:05:14 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "structs/t_env.h"
# include "structs/t_command.h"

void	exec_cmds(t_command *commands, t_env *env);
void	exec_builtins(t_command *commands, t_env *env);

#endif