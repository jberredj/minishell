/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:17:42 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 16:18:39 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DEBUG_H
# define _DEBUG_H
# include "structs/t_command.h"
# include "structs/t_token.h"

void	print_token(t_token *token);
void	print_commands(t_command *commands);
#endif