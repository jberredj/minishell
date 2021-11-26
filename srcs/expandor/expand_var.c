/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/23 16:52:10 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include "expandor.h"

void    expand_var(t_token *tokens, t_env *env)
{
    t_env_var   *existing;
    char        *content;
    char        *expanded_var;

    while (tokens)
    {
        content = tokens->content;
        if (content[0] == '$')
        {
            content++;
            existing = find_env_var_in_lst(env->env_vars, content)
        }
    }

}