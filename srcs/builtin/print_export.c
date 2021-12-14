/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:21:17 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/14 19:25:35 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
#include "env.h"
#include "builtin.h"

int		tab_size(char **tab)
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
	while(tab[i])
	{
		free_tab(&tab[i]);
		i++;
	}
	free(tab);
}
char	**sort_copy(char **arr)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (arr[i])
	{
		if (arr[i][0] > arr[i + 1][0])
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
		}
		i++;				
	}
	return (arr);
}

void	print_export(char **copy)
{
	int	i;
	
	i = 0;
	while (copy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(copy[i], 1);
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
	while ((*env).envp)
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
