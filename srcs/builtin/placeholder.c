/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:28:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/01 11:08:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "structs/t_env.h"

int	builtin_placeholder(char **argv, t_env *env)
{
	(void)argv;
	(void)env;
	printf("Oh no, looks like there's nothing here.\
Too bad the dev behind it such a lazyass that he still\
didn't implement it :(\n");
	return (0);
}
