/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:51:28 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/10 10:46:46 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENV_H
# define T_ENV_H
# include <stdint.h>
# include <stdbool.h>
# include "../../libft/includes/ft_lst.h"

typedef struct s_env_var
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
	size_t		nbr_vars;
	size_t		nbr_exported;
	t_list		*elems;
	char		**envp;
}				t_env;

#endif