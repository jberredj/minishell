/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:34:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 15:15:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "structs/t_command.h"
#include "../libft/includes/libft.h"
#include "exec.h"
#include "parser.h"
#include "env.h"
#include "minish_signal.h"
#include "error_codes.h"

int	exec_signals(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_sigaction = NULL;
	sig.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		return (CREATE_ERROR);
	return (SUCCESS);
}

int	restore_minish_ctrl_c(void)
{
	struct sigaction	sigint_act;

	ft_bzero(&sigint_act, sizeof(struct sigaction));
	sigint_act.sa_sigaction = ctrl_c;
	if (sigaction(SIGINT, &sigint_act, NULL) == -1)
		return (CREATE_ERROR);
	return (SUCCESS);
}

int	restore_external_signals(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_sigaction = NULL;
	sig.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		return (CREATE_ERROR);
	if (sigaction(SIGINT, &sig, NULL) == -1)
		return (CREATE_ERROR);
	return (SUCCESS);
}
