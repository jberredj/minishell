/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:23:22 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/12 23:51:11 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
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
	int	error;

	i = 0;
	if (!arg || !ft_isalpha(arg[0]) || arg[0] != '_')
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) || arg[i] != '_')
			return (print_err(error, &arg[i]) | SYNTAX_ERROR);
		i++;
	}
	return (SUCCESS);
}

void	set_or_update(t_env *env, char *arg, int i)
{
	int			j;
	char		*buff;
	t_env_var	*new;

	buff = NULL;
	while (arg[i] && arg[i] != '=')
		i++;
	buff = ft_calloc(sizeof(char), i + 1);
	if (!buff)
		return ;
	j = -1;
	while (++j < i)
		buff[j] = arg[j];
	new = find_env_var_in_lst(env->env_vars, buff);
	if (!new)
	{
		new = create_env_var_from_str(arg);
		add_env_var(env, new);
		env_var_to_envp(&env->envp, new, &env->nbr_exported);
	}
	else
	{
		update_env_var_value(new, &arg[i + 1]);
		update_envp_var_value(new, env->envp, &arg[i + 1]);
	}
	free (buff);
}

int	set_new_var(t_env *env, char *arg)
{
	t_env_var	*new;

	new = find_env_var_in_lst(env->env_vars, arg);
	if (new)
		env_var_to_envp(&env->envp, new, &env->nbr_exported);
	return (0);
}

int	export(char **argv, t_env *env)
{
	int			argc;
	int			i;

	argc = 0;
	i = 1;
	while (argv[argc])
		argc++;
	if (argc == 1)
		return (1); // export sans arguments - afficher env dans l'ordre
	while (argv[i])
	{
		if (check_arg_var(argv[i]))
		{
			if (ft_strchr(argv[i], '='))
				set_or_update(env, argv[i], 0);
			else
				set_new_var(env, argv[i]);
		}
		i++;
	}
	return (0);
