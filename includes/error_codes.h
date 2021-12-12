/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:55:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/12 19:39:13 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODES_H
# define ERROR_CODES_H
# define SUCCESS 0
# define ERR_MALLOC 1
# define SYNTAX_ERROR 2
# define PIPE_ERROR 4
# define CREATE_ERROR 8
# define UNKNOW_TOKEN 16
# define FILE_ERROR 32
# define RIGHT_ERROR 64
# define R_ERROR 128
# define W_ERROR 254
# define X_ERROR 512
# define NOT_EXIST_ERROR 1024
# define OPEN_ERROR	2048
# define HERE_DOC_ERROR 4096
# define UNFINISHED_LINE_ERROR 8192
# define ISNOTDIR_ERROR 16384
# define HOME_ERROR 32768
# define PWD_ERROR 131072
# define ERROR_INVALID_VAL 262144
# define EXIT 524288
# define ERROR_TOO_MANY 1048576
# define BUILTIN CD_ERROR + EXIT
# define BUILTIN_ERROR FILE_ERROR + HOME_ERROR + NOT_EXIST_ERROR + ISNOTDIR_ERROR + X_ERROR + ERROR_INVALID_VAL + ERROR_TOO_MANY
# define EXIT_ERROR ERROR_TOO_MANY + ERROR_INVALID_VAL

#endif