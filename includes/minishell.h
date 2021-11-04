/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:19:05 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/04 18:03:39 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/includes/ft_lst.h"

typedef struct s_env_elem
{
	bool	exported;
	char	*name;
	char	*value;
	char	*envp_str;
	int		id;
}				t_env_elem;
typedef struct s_env
{
	size_t		nbr_entry;
	t_list		*elems;
	char		**envp;

}				t_env;

int	parse_herited_envp(t_env *env, char **envp);
void  free_env_elem(void *elem);
#endif