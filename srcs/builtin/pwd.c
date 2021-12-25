/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:35:58 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/25 20:39:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../libft/includes/ft_io.h"
#include "structs/t_env.h"
#include "error_codes.h"

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
