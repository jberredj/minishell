/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:51:49 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 21:34:59 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# define ENV_VAR_EXPORTED 1
# define ENV_VAR_UPDATED 2
# include "../libft/includes/ft_lst.h"
# include "structs/t_env.h"

/*
** Create environment variable object
*/
t_env_var	*create_env_var(char *name, char *value);
t_env_var	*create_env_var_from_str(char *str);

/*
** Create exported (exposed in envp) environment variable object
*/
int			create_exported_var(t_env *env, char *name, char *value);
int			create_exported_var_from_str(t_env *env, char *str);

/*
** Remove environment variable object
*/
void		free_env_var(void *elem);
int			pop_env_var_from_env(t_env *env, char *name);
int			remove_from_envp(char ***envp, size_t *nbr_exported);

/*
** Add environment object to environment
*/
void		add_env_var(t_env *env, t_env_var *env_var_node);
int			add_new_envp(char ***envp, t_env_var *node, size_t *nbr_exported);

/*
** Update environment variable object
*/
void		update_envp_id(t_env_var *env_vars, int id);
int			update_env_var_value(t_env_var *env_var_node, char *value);
int			update_env_var_name(t_env_var *env_var_node, char *name);
int			update_envp_var_value(t_env_var *env_var_node, char **envp,
				char *value);
char		*update_envp_str(t_env_var *env_var_node);

/*
** Environment variable utils
*/
t_env_var	*find_env_var_in_lst(t_env_var *env_vars, char *name);
int			parse_herited_envp(t_env *env, char **envp);
char		*env_var_to_envp(char ***envp, t_env_var *env_var_node,
				size_t *nbr_exported);
char		**copy_envp(char **envp, int nbr);

#endif