/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:51:28 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/06 12:22:36 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENV_H
# define T_ENV_H
# include <stdint.h>
# include <stdbool.h>
# include "../../libft/includes/ft_idllst.h"

typedef struct s_env_var
{
	uint8_t		flags;
	char		*name;
	char		*value;
	char		*envp_str;
	int			id;
	t_idllist	list;
}				t_env_var;

typedef struct s_env
{
	bool		_update_envp;
	size_t		nbr_vars;
	size_t		nbr_exported;
	t_env_var	*env_vars;
	t_env_var	*path;
	t_env_var	*pwd;
	t_env_var	*old_pwd;
	t_env_var	*home;
	char		**envp;
	bool		running;
	uint8_t		exit_code;
	int			stdin_copy;
	int			stdout_copy;
}				t_env;

#endif