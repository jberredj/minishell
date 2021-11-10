/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_herited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:41:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/10 10:47:58 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	parse_herited_envp(t_env *env, char **envp)
{
	size_t		nbr_var;
	t_list		*lst_elem;
	t_env_var	*env_elem;
	int			i;

	nbr_var = 0;
	while (envp[nbr_var])
		nbr_var++;
	env->nbr_vars = nbr_var;
	i = -1;
	while (++i < nbr_var)
	{
		env_elem = create_env_var_from_str(envp[i], i); // TODO, PROTEGE LE CODE SALE MACAQUE
		lst_elem = ft_lstnew(env_elem);
		ft_lstadd_back(&env->elems, lst_elem);
	}
	return (0);
}
