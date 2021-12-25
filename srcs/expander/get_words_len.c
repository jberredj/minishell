/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_words_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:06:26 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/25 21:06:36 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

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
