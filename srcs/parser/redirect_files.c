/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:06:10 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/28 22:51:14 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../libft/includes/ft_idllst.h"
#include "structs/t_command.h"
#include "structs/t_token.h"
#include "error_codes.h"

int	parse_infile_redirect(t_command *command, t_token **tokens)
{
	if (ft_idllst_is_tail(&(*tokens)->list))
		return (SYNTAX_ERROR);
	*tokens = ft_idllst_next_content(&(*tokens)->list);
	if ((*tokens)->type == SEPARATOR)
		return (SYNTAX_ERROR);
	if (command->in_file)
		free(command->in_file);
	command->in_file = ft_strdup((*tokens)->content);
	if (!command->in_file)
		return (ERR_MALLOC);
	command->last_found = INFILE;
	return (SUCCESS);
}

int	parse_outfile_redirect(t_command *command, t_token **tokens, int mode)
{
	*tokens = ft_idllst_next_content(&(*tokens)->list);
	if (!*tokens)
		return (SYNTAX_ERROR);
	if ((*tokens)->type == SEPARATOR)
		return (SYNTAX_ERROR);
	if (command->out_file)
		free(command->out_file);
	command->out_file = ft_strdup((*tokens)->content);
	if (!command->out_file)
		return (ERR_MALLOC);
	command->out_mode = mode;
	command->last_found = OUTFILE;
	return (SUCCESS);
}
