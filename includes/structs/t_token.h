/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:31:40 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 21:28:42 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TOKEN_H
# define T_TOKEN_H
# include "../../libft/includes/ft_idllst.h"
# define WORD 1
# define SEPARATOR 2
# define S_QUOTE '\''
# define D_QUOTE '\"'

typedef struct s_token
{
	int			type;
	char		*content;
	t_idllist	list;
}				t_token;

#endif