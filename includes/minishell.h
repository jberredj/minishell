/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:19:05 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 20:16:47 by jberredj         ###   ########.fr       */
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

int	init_sh(t_env *env, char **envp);
#endif