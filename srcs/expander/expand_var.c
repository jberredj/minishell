/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:07 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/26 18:16:06 by ddiakova         ###   ########.fr       */
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
        if (content[0] == '$' && tokens->type != S_QUOTE)
        {
            content++;
            existing = find_env_var_in_lst(env->env_vars, content);
            if (existing)
                expanded_var = ft_strdup(existing->value);
            else 
                expanded_var = ft_strdup("");
                //ft_idllst_pop(&tokens->list, free_token(tokens->content));
        free(tokens->content);
        tokens->content = expanded_var;
        }
        else
            printf ("%s\n", tokens->content);
        ft_idllist_next_content(&tokens->list);
    }
}