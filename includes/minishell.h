/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:19:05 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/08 14:59:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include "../libft/includes/ft_lst.h"

# define ENV_VAR_EXPORTED 1
# define ENV_VAR_UPDATED 2

typedef struct s_env_elem
{
	uint8_t	flags;
	char	*name;
	char	*value;
	char	*envp_str;
	int		id;
}				t_env_var;
typedef struct s_env
{
	bool		_update_envp;
	size_t		nbr_entry;
	t_list		*elems;
	char		**envp;

}				t_env;

#ifdef DEBUG
void	debug_print(t_env *env);
#endif

int			pop_env_var(t_env *env, char *name);
int			add_env_var(t_env *env, t_env_var *elem);
t_env_var	*create_env_var(char *name, char *value, int id);
t_env_var	*create_env_var_from_str(char *str, int id);
int			parse_herited_envp(t_env *env, char **envp);
void		free_env_var(void *elem);
#endif