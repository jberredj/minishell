/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:19:05 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/25 15:08:34 by jberredj         ###   ########.fr       */
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
	int		dup_stdin;
	int		dup_stdout;
}				t_sh_dat;

#endif