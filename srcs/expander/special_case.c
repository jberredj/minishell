/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:05:55 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/25 21:07:37 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "structs/t_env.h"
#include "structs/t_token.h"
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
