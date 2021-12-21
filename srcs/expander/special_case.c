/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:05:55 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/21 15:08:55 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include "expander.h"
#include "env.h"
#include "tokeniser.h"
#include <stdio.h>
#include "_debug.h"
#include "error_codes.h"

int	exit_code_var(t_env *env, t_token *expanded_value)
{
	char	*tmp;

	tmp = ft_itoa(env->exit_code);
	if (!tmp)
		return (ERR_MALLOC);
	free(expanded_value->content);
	expanded_value->content = tmp;
	return (SUCCESS);
}

int	dollar_alone(t_token *expanded_value)
{
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (ERR_MALLOC);
	free(expanded_value->content);
	expanded_value->content = tmp;
	return (SUCCESS);
}
