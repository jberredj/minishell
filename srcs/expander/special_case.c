/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:05:55 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/07 19:06:29 by ddiakova         ###   ########.fr       */
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

void	exit_code_var(t_env *env, t_token *expanded_value)
{
	char	*tmp;

	tmp = ft_itoa(env->exit_code);
	free (expanded_value->content);
	expanded_value->content = tmp;
}

void	dollar_alone(t_token *expanded_value)
{
	char	*tmp;

	tmp = ft_strdup("$");
	free (expanded_value->content);
	expanded_value->content = tmp;
}
