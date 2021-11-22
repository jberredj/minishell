/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:19:05 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/22 22:37:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef VERSION_NUMBER
#  define VERSION_NUMBER "unknown"
# endif
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include "structs/t_env.h"

typedef struct s_sh_dat
{
	t_env	env;
}				t_sh_dat;

int	echo(char **argv, char **envp);

#endif