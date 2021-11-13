/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_herited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:41:15 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/12 16:34:00 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	parse_herited_panic(t_list *env_lst, t_env_var *elem)
{
	if (elem)
		free(elem);
	ft_lstclear(&env_lst, free_env_var);
	return (1);
}

void	set_parsed_vars_in_env(t_env *env)
{
	t_list		*lst_elem;

	lst_elem = find_env_var_in_lst(&env->elems, "PATH");
	if (lst_elem)
		env->path = lst_elem->content;
	lst_elem = find_env_var_in_lst(&env->elems, "PWD");
	if (lst_elem)
		env->pwd = lst_elem->content;
	lst_elem = find_env_var_in_lst(&env->elems, "OLDPWD");
	if (lst_elem)
		env->old_pwd = lst_elem->content;
	lst_elem = find_env_var_in_lst(&env->elems, "HOME");
	if (lst_elem)
		env->home = lst_elem->content;
}

int	parse_herited_envp(t_env *env, char **envp)
{
	size_t		nbr_var;
	t_list		*env_lst;
	t_list		*lst_elem;
	t_env_var	*env_elem;
	int			i;

	nbr_var = 0;
	while (envp[nbr_var])
		nbr_var++;
	env->nbr_vars = nbr_var;
	i = -1;
	env_lst = NULL;
	while (++i < (int)nbr_var)
	{
		env_elem = create_env_var_from_str(envp[i], i);
		if (!env_elem)
			return (parse_herited_panic(env_lst, NULL));
		lst_elem = ft_lstnew(env_elem);
		if (!lst_elem)
			return (parse_herited_panic(env_lst, env_elem));
		ft_lstadd_back(&env_lst, lst_elem);
	}
	env->elems = env_lst;
	set_parsed_vars_in_env(env);
	return (0);
}
