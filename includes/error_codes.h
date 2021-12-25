/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:55:31 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/25 21:39:56 by jberredj         ###   ########.fr       */
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
# define R_ERROR 128
# define W_ERROR 254
# define X_ERROR 512
# define NOT_EXIST 1024
# define OPEN_ERROR	2048
# define HERE_DOC_ERROR 4096
# define UNFINISHED_LINE 8192
# define ISNOTDIR 16384
# define HOME_ERROR 32768
# define PWD_ERROR 65536
# define INVALID_VAL 131072
# define TOO_MANY 262144
# define CANCEL 524288
# define NOT_FOUND 1048576
# define SKIP 2097152
# define FATAL_ERROR 4194304
# define CHECK_BUILTIN 8388608
#endif