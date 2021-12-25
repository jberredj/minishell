/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:35:58 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/25 17:59:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/ft_io.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
#include "env.h"
#include "builtin.h"
#include <stdio.h>

int	pwd(char **argv, t_env *env)
{
	char	*pwd;

	(void)argv;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd: getcwd() failed:");
		return (PWD_ERROR);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (SUCCESS);
}
