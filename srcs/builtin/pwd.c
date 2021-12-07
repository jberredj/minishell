/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:35:58 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/06 17:36:46 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/ft_io.h"
#include "minishell.h"
#include "error_codes.h"
#include <fcntl.h>
#include "env.h"
#include "builtin.h"

int	pwd(char **argv, t_env *env)
{
	char	*pwd;

	(void)argv;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (PWD_ERROR);
	ft_putendl_fd(pwd, 1);
	return (SUCCESS);
}
