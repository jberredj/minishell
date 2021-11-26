/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:20:45 by ddiakova          #+#    #+#             */
/*   Updated: 2021/11/26 18:37:55 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "structs/t_env.h"
# include "structs/t_token.h"
# include "../libft/includes/ft_idllst.h"

void	expand_var(t_token *tokens, t_env *env);

#endif