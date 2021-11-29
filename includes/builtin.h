/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:54:47 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/29 19:17:26 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"
# include "structs/t_command.h"
# include "structs/t_env.h"
# include "structs/t_token.h"

int	check_builtin(t_command *commands, t_env_var *path, t_token cmd_tok);
int	cd(t_sh_dat *shdat, char **argv);
int	echo(char **argv, char **envp);
int	builtin_placeholder(char **argv, char **envp);
#endif