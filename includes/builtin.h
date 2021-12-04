/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:54:47 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/04 21:47:21 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# define BUFFER_SIZE 1024
# include "minishell.h"
# include "structs/t_command.h"
# include "structs/t_env.h"
# include "structs/t_token.h"

int	check_builtin(t_command *commands, t_env_var *path, t_token cmd_tok);
int	echo(char **argv, t_env *env);
int	cd(char **argv, t_env *env);
int	minish_exit(char **argv, t_env *env);
int	builtin_placeholder(char **argv, t_env *env);
#endif