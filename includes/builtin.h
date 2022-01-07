/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:54:47 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/07 15:05:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "structs/t_command.h"
# include "structs/t_env.h"
# include "structs/t_token.h"

int		check_builtin(t_command *commands, t_env_var *path, t_token cmd_tok);
int		echo(char **argv, t_env *env);
int		cd(char **argv, t_env *env);
int		pwd(char **argv, t_env *env);
int		env(char **argv, t_env *env);
int		unset(char **argv, t_env *env);
int		minish_exit(char **argv, t_env *env);
int		export(char **argv, t_env *env);
int		copy_envp_and_print(t_env *env);
int		check_args(char **argv);
int		check_access(char *path);
int		print_error(int error, char *path);
int		set_env_var(t_env *env, t_env_var *var, char *name, char *var_to_set);
int		update_env(t_env *env, char *cwd);
int		set_pwd(t_env *env);
char	*get_cwd_err_protected(t_env *env);
char	**copy_envp_not_set_exported(t_env_var *env_vars, char **envp,
			size_t *nbr);
#endif