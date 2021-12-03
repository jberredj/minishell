/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dariadiakova <dariadiakova@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:06:35 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/02 21:38:07 by dariadiakov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs/t_token.h"
#include "../libft/includes/ft_idllst.h"

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
