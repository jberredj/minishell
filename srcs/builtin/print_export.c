/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:21:17 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/05 23:23:46 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "error_codes.h"
#include "env.h"
#include "builtin.h"
#include "parser.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

char	**sort_copy(char **arr, int array_size)
{
	int		i;
	int		j;
	char	*tmp;

	i = array_size - 1;
	tmp = NULL;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i--;
	}
	return (arr);
}

void	print_export(char **copy)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	while (copy[i])
	{
		index = 0;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (copy[i][j])
		{
			ft_putchar_fd(copy[i][j], 1);
			if (copy[i][j] == '=')
			{
				ft_putchar_fd('"', 1);
				index++;
			}
			j++;
		}
		if (index == 1)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	copy_envp_and_print(t_env *env)
{
	char	**copy;
	size_t	nbr_var;

	nbr_var = env->nbr_exported;
	copy = copy_envp_not_set_exported(env->env_vars, env->envp, &nbr_var);
	if (!copy)
	{
		env->error_in_builtin = ERR_MALLOC;
		return (ERR_MALLOC);
	}
	sort_copy(copy, nbr_var);
	print_export(copy);
	free_xv(copy);
	return (SUCCESS);
}
