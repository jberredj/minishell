/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:28:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/29 22:27:48 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	builtin_placeholder(char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	printf("Oh no, looks like there's nothing here.\
Too bad the dev behind it such a lazyass that he still\
didn't implement it :(\n");
	return (0);
}
