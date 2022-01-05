/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:23:22 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/06 00:31:18 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "error_codes.h"
#include "env.h"
#include "builtin.h"

int	print_err(int error, char *path)
{
	ft_putstr_fd("minishell: export : ", 2);
	if (error & SYNTAX_ERROR)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
	return (1);
}

int	check_arg_var(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (print_err(SYNTAX_ERROR, arg));
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (print_err(SYNTAX_ERROR, &arg[i]));
		i++;
	}
	return (SUCCESS);
}

int	set_or_update(t_env *env, char *arg)
{
	t_env_var	*found;
	char		*equal;
	int			error;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (SUCCESS);
	*equal = '\0';
	found = find_env_var_in_lst(env->env_vars, arg);
	*equal = '=';
	error = 0;
	if (!found)
	{
		if (create_exported_var_from_str(env, arg))
			error = ERR_MALLOC;
	}
	else
	{
		if (update_envp_var_value(found, env->envp, equal + 1)
			|| !env_var_to_envp(&env->envp, found, &env->nbr_exported))
			error = ERR_MALLOC;
	}
	if (error)
		env->error_in_builtin = error;
	return (error);
}

int	set_new_var(t_env *env, char *arg)
{
	t_env_var	*new;

	new = find_env_var_in_lst(env->env_vars, arg);
	if (new)
	{
		if (new->flags != NOT_SET_EXPORTED
			&& !env_var_to_envp(&env->envp, new, &env->nbr_exported))
		{
			env->error_in_builtin = ERR_MALLOC;
			return (ERR_MALLOC);
		}
	}
	else
	{
		new = create_env_var(arg, "");
		if (!new)
			return (ERR_MALLOC);
		add_env_var(env, new);
		new->flags = NOT_SET_EXPORTED;
	}
	return (SUCCESS);
}

int	export(char **argv, t_env *env)
{
	int			argc;
	int			i;
	int			error;

	argc = 0;
	i = 1;
	while (argv[argc])
		argc++;
	error = SUCCESS;
	if (argc == 1)
		return (copy_envp_and_print(env));
	while (argv[i])
	{
		if (!check_arg_var(argv[i]))
		{
			if (ft_strchr(argv[i], '='))
				error = set_or_update(env, argv[i]);
			else
				error = set_new_var(env, argv[i]);
		}
		i++;
	}
	return (error);
}
