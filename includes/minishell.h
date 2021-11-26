/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:19:05 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/26 18:38:10 by ddiakova         ###   ########.fr       */
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
# include "structs/t_token.h"
# include "expander.h"

typedef struct s_sh_dat
{
	t_env	env;
	t_token token;
}				t_sh_dat;


#endif