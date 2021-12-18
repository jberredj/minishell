/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:21:17 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/18 18:44:20 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
#include "env.h"
#include "builtin.h"

int	tab_size(char **tab)
{	
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**sort_copy(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = tab_size(arr) - 1;
	tmp = NULL;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strncmp(arr[j], arr[j + 1], 1) > 0)
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
	int		size;
	int		i;
	char	**copy;

	size = tab_size((*env).envp);
	copy = ft_calloc(sizeof(char *), size + 1);
	if (!copy)
		return (1);
	i = 0;
	while ((*env).envp[i])
	{
		copy[i] = ft_calloc(sizeof(char), ft_strlen((*env).envp[i]) + 1);
		if (!copy[i])
			return (1);
		copy[i] = (*env).envp[i];
		i++;
	}
	copy[i] = NULL;
	sort_copy(copy);
	print_export(copy);
	free_tab(copy);
	return (0);
}
