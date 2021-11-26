/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/23 16:52:10 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDOR_H
# define EXPONDOR_H
# include "structs/t_env.h"
# include "structs/t_token.h"

void    expand_var(t_token *tokens, t_env *env);

#endif