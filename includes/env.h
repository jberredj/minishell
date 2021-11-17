/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:51:49 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 11:56:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# define ENV_VAR_EXPORTED 1
# define ENV_VAR_UPDATED 2
# include "../libft/includes/ft_lst.h"
# include "structs/t_env.h"

int			pop_env_var_from_env(t_env *env, char *name);
int			add_env_var(t_env *env, t_env_var *env_var_node);
t_env_var	*create_env_var(char *name, char *value, int id);
t_env_var	*create_env_var_from_str(char *str, int id);
int			parse_herited_envp(t_env *env, char **envp);
void		free_env_var(void *elem);
int			update_env_var_value(t_env_var *env_var_node, char *value);
int			update_env_var_name(t_env_var *env_var_node, char *name);
int			pop_env_var_from_env(t_env *env, char *name);
t_env_var	*find_env_var_in_lst(t_env_var *env_vars, char *name);
#endif