/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:05:12 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/12 21:06:18 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_SIGNAL_H
# define MINISH_SIGNAL_H
# include <signal.h>
void	ctrl_c(int sig, siginfo_t *info, void *ctx);

#endif