/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:33:20 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 16:52:29 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "structs/t_token.h"
#include "structs/t_command.h"
#include "../libft/includes/ft_idllst.h"

void	print_token(t_token *token)
{
	while (token)
	{
		printf("current token: %s\ntype : %d\n", token->content, token->type);
		token = ft_idllst_next_content(&token->list);
	}
}

void	print_commands(t_command *commands)
{
	int	i;

	while (commands)
	{
		printf("command : %s \nargv : [", commands->path_to_cmd);
		i = -1;
		while (commands->argv[++i])
			printf("\"%s\", ", commands->argv[i]);
		printf("NULL]\n");
		commands = ft_idllst_next_content(&commands->list);
	}
}
