/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:06:10 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/22 17:59:08 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "structs/t_command.h"
#include "structs/t_token.h"
#include "error_codes.h"
#include "../libft/includes/ft_idllst.h"

int	parse_infile_redirect(t_command *command, t_token **tokens)
{
	int	fd;

	if (ft_idllst_is_tail(&(*tokens)->list))
		return (SYNTAX_ERROR);
	*tokens = ft_idllst_next_content(&(*tokens)->list);
	if ((*tokens)->type == SEPARATOR)
		return (SYNTAX_ERROR);
	command->in_file = ft_strdup((*tokens)->content);
	if (!command->in_file)
		return (ERR_MALLOC);
	command->last_found = INFILE;
	return (SUCCESS);
}

int	parse_outfile_redirect(t_command *command, t_token **tokens, int mode)
{
	int	fd;

	*tokens = ft_idllst_next_content(&(*tokens)->list);
	if (!*tokens)
		return (SYNTAX_ERROR);
	if ((*tokens)->type == SEPARATOR)
		return (SYNTAX_ERROR);
	command->out_file = ft_strdup((*tokens)->content);
	if (!command->out_file)
		return (ERR_MALLOC);
	command->out_mode = mode;
	command->last_found = OUTFILE;
	return (SUCCESS);
}
