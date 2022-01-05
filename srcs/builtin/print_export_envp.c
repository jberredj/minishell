/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 23:23:26 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/06 00:01:03 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "error_codes.h"
#include "env.h"
#include "builtin.h"
#include "parser.h"

static void	reset_env_vars_flags(t_env_var *node)
{
	node->flags = NOT_SET_EXPORTED;
	node->envp_str = NULL;
}

static char	**final_copy(t_env_var *vars, char **envp, size_t nbr)
{
	char	**final_envp;

	final_envp = copy_envp(envp, (int)nbr);
	while (vars)
	{
		if (vars->flags == NOT_SET_EXPORTED)
		{
			envp[vars->id] = NULL;
			vars->id = -1;
		}
		vars = ft_idllst_next_content(&vars->list);
	}
	free_xv(envp);
	return (final_envp);
}

static char	**error_in_copy(t_env_var *vars, char **envp)
{
	while (vars)
	{
		if (vars->flags == NOT_SET_EXPORTED)
		{
			envp[vars->id] = NULL;
			vars->id = -1;
		}
		vars = ft_idllst_next_content(&vars->list);
	}
	free_xv(envp);
	return (NULL);
}

char	**copy_envp_not_set_exported(t_env_var *env_vars, char **envp,
	size_t *nbr)
{
	char		**export_envp;
	int			error;
	t_env_var	*vars;

	export_envp = copy_envp(envp, (int)(*nbr));
	if (!export_envp)
		return (NULL);
	error = 0;
	vars = env_vars;
	while (env_vars)
	{
		if (env_vars->flags == NOT_SET_EXPORTED)
		{
			env_vars->envp_str = env_vars->name;
			if (add_new_envp(&export_envp, env_vars, nbr))
				error = ERR_MALLOC;
			reset_env_vars_flags(env_vars);
		}
		if (error)
			return (error_in_copy(vars, export_envp));
		env_vars = ft_idllst_next_content(&env_vars->list);
	}
	return (final_copy(vars, export_envp, *nbr));
}
