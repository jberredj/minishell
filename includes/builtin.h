/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:54:47 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/06 17:35:08 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"
# include "structs/t_command.h"
# include "structs/t_env.h"
# include "structs/t_token.h"

int	check_builtin(t_command *commands, t_env_var *path, t_token cmd_tok);
int	echo(char **argv, t_env *env);
int	cd(char **argv, t_env *env);
int	pwd(char **argv, t_env *env);
int	check_args(char **argv);
int	check_access(char *path);
int	print_error(int error, char *path);
int	set_env_var(t_env *env, t_env_var *var, char *name, char *var_to_set);
int	update_env(t_env *env, char *cwd);
int	minish_exit(char **argv, t_env *env);
int	builtin_placeholder(char **argv, t_env *env);
#endif