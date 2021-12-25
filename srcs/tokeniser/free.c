/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:06:35 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 21:23:14 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/ft_idllst.h"
#include "structs/t_token.h"

void	free_token(void *content)
{
	t_token	*token;

	token = ft_idllst_content(content);
	if (token)
	{
		if (token->content)
			free(token->content);
		free(token);
	}
}
