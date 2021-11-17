/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:39:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 10:50:10 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_env.h"
#include "env.h"
#include "../libft/includes/ft_lst.h"
#include "../libft/includes/ft_string.h"

t_list	*find_env_var_in_lst(t_list **env_lst, char *name)
{
	t_list		*lst_elem;
	t_env_var	*env_elem;

	lst_elem = *env_lst;
	env_elem = (t_env_var *)lst_elem->content;
	while (lst_elem && ft_strncmp(env_elem->name, name, ft_strlen(name)) != 0)
	{
		lst_elem = lst_elem->next;
		if (lst_elem)
			env_elem = (t_env_var *)lst_elem->content;
	}
	return (lst_elem);
}

int	pop_env_var_from_env(t_env *env, char *name)
{
	t_list		*lst_elem;
	t_env_var	*env_elem;

	lst_elem = find_env_var_in_lst(&env->elems, name);
	if (!lst_elem)
		return (1);
	env->nbr_vars--;
	env_elem = lst_elem->content;
	if (env_elem->flags & ENV_VAR_EXPORTED)
	{
		env->_update_envp = true;
		env->envp[env_elem->id] = NULL;
	}
	ft_lstpop(&env->elems, lst_elem, free_env_var);
	return (0);
}

int	add_env_var(t_env *env, t_env_var *elem)
{
	t_list	*lst_elem;

	lst_elem = ft_lstnew(elem);
	if (!lst_elem)
		return (-1);
	ft_lstadd_back(&env->elems, lst_elem);
	env->nbr_vars++;
	return (0);
}
