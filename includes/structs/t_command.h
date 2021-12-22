/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:54:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 12:13:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMMAND_H
# define T_COMMAND_H
# include "structs/t_env.h"
# include "../libft/includes/ft_idllst.h"
# include <sys/types.h>
# define PIPE_IN 1
# define PIPE_OUT 2
# define INFILE 1
# define OUTFILE 2

typedef struct s_command
{
	char		*path_to_cmd;
	int			(*builtin)(char**, t_env *);
	int			argc;
	char		**argv;
	char		**envp;
	char		*in_file;
	char		*out_file;
	int			out_mode;
	int			last_found;
	bool		piped;
	int			fd_in;
	int			fd_out;
	pid_t		process;
	int			exit_code;
	t_idllist	list;
}				t_command;
#endif