/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:02:10 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/21 17:44:56 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "../../libft/includes/ft_io.h"
#include "minishell.h"
#include <limits.h>

int	cd(t_sh_dat *shdat, char **argv)
{	
	int		argc;
	char	path[PATH_MAX];
	t_env_var *pwd;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (-1);
	}
	if (argc == 1)
	{
		pwd = shdat->env.pwd;
		if (pwd == NULL)
			return (1);
		getcwd(path, PATH_MAX);
		
	}
	return (0);
}