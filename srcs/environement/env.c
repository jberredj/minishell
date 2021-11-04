/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:42:34 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/04 16:29:12 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

int	_update_envp_str(t_env_elem *elem)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(elem->name, "=");
	if (!tmp)
		return (-1); //  CHANGE THIS TO PROPER MALLOC ERROR CODE
	ft_gnljoin(&tmp, elem->value);
	if (!tmp)
		return (-1); // CF AU DESSUS
	elem->envp_str = tmp;
	return (0); 
}

int	update_env_elem_name(t_env_elem *elem, char *name)
{
	char	*tmp;

	tmp = ft_strdup(name);
	if (!tmp)
		return (-1); // CHANGE THIS TO PROPER MALLOC ERROR CODE
	if (elem->name)
		free(elem->name);
	elem->name = tmp;
	return (0);
}

int	update_env_elem_value(t_env_elem *elem, char *value)
{
	char	*tmp;

	tmp = ft_strdup(value);
	if (!tmp)
		return (-1); // CHANGE THIS TO PROPER MALLOC ERROR CODE
	if (elem->value)
		free(elem->value);
	elem->value = tmp;
	if (elem->name)
		return (_update_envp_str(elem));
	return (0);
}

t_env_elem *create_env_elem(char *name, char *value, int id)
{
	t_env_elem	*elem;

	elem = (t_env_elem *)ft_calloc(1, sizeof(t_env_elem));
	if (!elem)
		return (NULL);
	elem->id = id;
	update_env_elem_name(elem, name);
	update_env_elem_value(elem, value);
	return (elem);
}

t_env_elem	*create_en_elem_from_str(char *str, int id)
{
	t_env_elem	*elem;
	size_t		equal_loc;
	char		*name;
	char		*value;

	value = ft_strchr(str, '=');
	if (!value && *(value + 1) && value != str)
		return (NULL);
	equal_loc = (size_t)((value - str));
	value++;
	name = ft_calloc(equal_loc, sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, equal_loc + 1);
	elem = create_env_elem(name, value, id);
	free(name);
	return (elem);
}


#ifdef DEBUG
void	debug_print(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->nbr_entry)
		printf("name : %s\tvalue : %s\n", env->elems[i]->name, env->elems[i]->value);
}
#endif

int	parse_herited_envp(t_env *env, char **envp)
{
	size_t	nbr_var;
	int		i;

	nbr_var = 0;
	while (envp[nbr_var])
		nbr_var++;
	env->nbr_entry = nbr_var;
	env->elems = (t_env_elem **)ft_calloc(nbr_var, sizeof(t_env_elem *));
	if (!env->elems)
		return (-1);
	i = -1;
	while (++i < nbr_var)
		env->elems[i] = create_en_elem_from_str(envp[i], i); // TODO, PROTEGE LE CODE SALE MACAQUE
	#ifdef DEBUG
		debug_print(env);
	#endif
}