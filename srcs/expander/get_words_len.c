/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:06:26 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/21 14:46:57 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs/t_env.h"
#include "structs/t_token.h"
#include "../libft/includes/libft.h"
#include "expander.h"
#include "env.h"
#include "tokeniser.h"
#include "_debug.h"

int	get_words_len(char *line, bool min_val)
{
	int	len;

	if (min_val)
		return (1);
	len = 0;
	while (line[len] && (line[len] != '$'))
		len++;
	return (len);
}