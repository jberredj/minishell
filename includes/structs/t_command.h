/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:54:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/23 15:29:14 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMMAND_H
# define T_COMMAND_H
# include "../libft/includes/ft_idllst.h"

typedef struct s_command
{
	char		*path_to_cmd;
	int			(*builtin)(char**, char**);
	int			argc;	
	char		**argv;
	char		**envp;
	t_idllist	list;
}				t_command;
#endif