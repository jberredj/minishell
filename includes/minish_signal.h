/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:05:12 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 22:06:20 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_SIGNAL_H
# define MINISH_SIGNAL_H
# include <signal.h>

int		restore_external_signals(void);
void	ctrl_c(int sig, siginfo_t *info, void *ctx);
int		exec_signals(void);
int		restore_minish_ctrl_c(void);
#endif