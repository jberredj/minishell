/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:00:01 by ddiakova          #+#    #+#             */
/*   Updated: 2021/12/25 21:05:55 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

int	get_var_len(char *line, bool min_val)
{
	int	len;

	if (min_val)
		return (0);
	len = 0;
	if (line[0] == '?' || ft_isdigit(line[0]))
		return (1);
	while (line[len] && (ft_isalnum(line[len]) || line[len] == '_'))
		len++;
	return (len);
}
