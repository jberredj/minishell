/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_set_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 19:51:04 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 20:29:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_codes.h"
#include "env.h"
#include "builtin.h"

int	set_pwd(t_env *env)
{
	char	*pwd;
	int		error;

	pwd = get_cwd_err_protected(env);
	if (!pwd)
		return (ERR_MALLOC);
	error = set_env_var(env, env->pwd, "PWD", pwd);
	if (error == 2)
		update_envp_var_value(env->pwd, env->envp, pwd);
	free(pwd);
	if (error == ERR_MALLOC)
		return (ERR_MALLOC);
	return (SUCCESS);
}
