# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 15:10:49 by jberredj          #+#    #+#              #
#    Updated: 2021/11/17 10:32:12 by jberredj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
CC				=	clang
OPTI			=	-O2
CFLAGS			=	-Wall -Werror -Wextra $(OPTI)

BUFFER_SIZE		=	32

SRC_DIR			= 	srcs
INC_DIR			=	includes
OBJ_DIR			=	objs

###############################################################################
##								Source files								 ##
###############################################################################

FT_CTYPE		= 	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isblank.c \
					ft_iscntrl.c ft_isdigit.c ft_isgraph.c ft_islower.c \
					ft_isprint.c ft_ispunct.c ft_isspace.c ft_isupper.c \
					ft_isxdigit.c
FT_CTYPE_SRCS	=	$(addprefix srcs/ft_ctype/, $(FT_CTYPE))
FT_CTYPE_OBJS	=	$(addprefix objs/ft_ctype., $(subst /,., $(subst srcs/,, $(FT_CTYPE:.c=.o))))

FT_LST			= 	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
					ft_lstnew.c ft_lstpop.c ft_lstsize.c
FT_LST_SRCS		=	$(addprefix srcs/ft_lst/, $(FT_LST))
FT_LST_OBJS		=	$(addprefix objs/ft_lst., $(subst /,., $(subst srcs/,, $(FT_LST:.c=.o))))

FT_IDLLST		= 	ft_idllst_add_after.c ft_idllst_add_before.c \
					ft_idllst_clear.c ft_idllst_clear_before.c \
					ft_idllst_content.c ft_idllst_get_tail.c \
					ft_idllst_is_head.c ft_idllst_nbr_to_head.c \
					ft_idllst_pop.c ft_idllst_add_back.c ft_idllst_add_front.c \
					ft_idllst_clear_after.c ft_idllst_del.c \
					ft_idllst_get_head.c ft_idllst_init.c \
					ft_idllst_is_tail.c ft_idllst_nbr_to_tail.c \
					ft_idllst_size.c ft_idllst_is_init.c \
					ft_idllst_prev_content.c ft_idllst_next_content.c
FT_IDLLST_SRCS	=	$(addprefix srcs/ft_idllst/, $(FT_IDLLST))
FT_IDLLST_OBJS	=	$(addprefix objs/ft_idllst., $(subst /,., $(subst srcs/,, $(FT_IDLLST:.c=.o))))

FT_IO			=	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c ft_putnbr_base_fd.c ft_put_unbr_fd.c
FT_IO_SRCS		=	$(addprefix srcs/ft_io/, $(FT_IO))
FT_IO_OBJS		=	$(addprefix objs/ft_io., $(subst /,., $(subst srcs/,, $(FT_IO:.c=.o))))

FT_STRING		=	ft_cw_sep.c ft_split.c ft_strchr.c \
					ft_strrchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
					ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
					ft_strnstr.c ft_strtrim.c ft_substr.c	ft_bzero.c \
					ft_calloc.c ft_memccpy.c ft_memcpy.c ft_memcmp.c \
					ft_memchr.c ft_memmove.c ft_memset.c
FT_STRING_SRCS	=	$(addprefix srcs/ft_string/, $(FT_STRING))
FT_STRING_OBJS	=	$(addprefix objs/ft_string., $(subst /,., $(subst srcs/,, $(FT_STRING:.c=.o))))

FT_TO			=	ft_atoi.c ft_itoa.c ft_intlen.c ft_intlen_base.c \
					ft_lllen_base.c ft_uitoa.c ft_uintlen.c ft_lltoa.c \
					ft_ulltoa.c ft_ulllen.c ft_lllen.c ft_tolower.c \
					ft_toupper.c ft_ulllen_base.c ft_ulltoa_base.c \
					ft_atof.c ft_atoui32_base.c
FT_TO_SRCS		=	$(addprefix srcs/ft_to/, $(FT_TO))
FT_TO_OBJS		=	$(addprefix objs/ft_to., $(subst /,., $(subst srcs/,, $(FT_TO:.c=.o))))

FT_UTILS		=	check_base.c ft_swap.c ft_abs.c
FT_UTILS_SRCS	=	$(addprefix srcs/ft_utils/, $(FT_UTILS))
FT_UTILS_OBJS	=	$(addprefix objs/ft_utils., $(subst /,., $(subst srcs/,, $(FT_UTILS:.c=.o))))

GET_NEXT_LINE	=	get_next_line.c get_next_line_utils.c
GNL_SRCS		=	$(addprefix srcs/get_next_line/, $(GET_NEXT_LINE))
GNL_OBJS		=	$(addprefix objs/get_next_line., $(subst /,., $(subst srcs/,, $(GET_NEXT_LINE:.c=.o))))

LIBS_OBJS		=	$(FT_CTYPE_OBJS) $(FT_LST_OBJS) $(FT_IO_OBJS) \
					$(FT_STRING_OBJS) $(FT_TO_OBJS) $(FT_UTILS_OBJS) \
					$(GNL_OBJS) $(FT_IDLLST_OBJS)
LIBS_SRCS		=	$(FT_CTYPE_SRCS) $(FT_LST_SRCS) $(FT_IO_SRCS) \
					$(FT_STRING_SRCS) $(FT_TO_SRCS) $(FT_UTILS_SRCS) \
					$(GNL_SRCS) $(FT_IDLLST_SRCS)

LIBS			=	ft_ctype ft_lst ft_io ft_string ft_to ft_utils \
					get_next_line

HEADERS			=	ft_ctype.h ft_io.h ft_lst.h ft_string.h ft_to.h \
					ft_utils.h get_next_line.h ft_idllst.h libft.h

###############################################################################
##							Color output char								 ##
###############################################################################
BLUE			=\033[0;34m
NC				=\033[0m
LIGHT_PURPLE	=\033[1;35m
YELLOW			=\033[1;33m
GREEN			=\033[0;32m
RED				=\033[0;31m

###############################################################################
## 							Mandatory recipes								 ##
###############################################################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBS_OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$(NAME) $(BLUE)library$(NC)\n"
	ar cr $(NAME) objs/*.o
	printf "$(GREEN)Completed$(NC)\n"
	
clean:
	printf "$(RED)Removing objects files$(NC)\n"
	rm -rf objs
	rm -rf *.o;

fclean: clean
	printf "$(RED)Removing $(LIGHT_PURPLE)$(NAME) \
	$(RED)library\n$(NC)\n"	
	rm -rf $(NAME)

re: fclean all

###############################################################################
## 								Extra recipes								 ##
###############################################################################

define COMPILE
	find ./objs/ -type f -exec touch {} +
	$(foreach source,$?, \
	printf "$(YELLOW)[..]  $(NC) $(LIGHT_PURPLE)$(subst srcs/,,$(source))$(NC)\n"; \
	$(CC) -I $(INC_DIR) $(CFLAGS) $(CODE_VERSION) -c $(source) -o $(subst /,.,$(subst srcs/,,$(source:.c=.o))) ; \
	if [ $$? -ne "0" ];\
	then \
		exit 1;\
	fi; \
	norminette $(source) > /dev/null ;\
	if [ $$? -ne "0" ];\
	then \
		printf "\033[F$(RED)[NORM]$(NC) $(LIGHT_PURPLE)$(subst srcs/,,$(source))$(NC)\n";\
	else \
		printf "\033[F$(GREEN)[OK]  $(NC) $(LIGHT_PURPLE)$(subst srcs/,,$(source))$(NC)\n";\
	fi;)
	mv *.o objs/
endef

lib: 
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$(NAME) $(BLUE)library$(NC)\n"
	ar cr $(NAME) objs/*.o
	printf "$(GREEN)Completed$(NC)\n"

ft_ctype: $(OBJ_DIR) $(FT_CTYPE_OBJS)
$(FT_CTYPE_OBJS): $(FT_CTYPE_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)ft_ctype $(BLUE)functions$(NC)\n"
	$(COMPILE)

ft_string: $(OBJ_DIR) $(FT_STRING_OBJS)
$(FT_STRING_OBJS): $(FT_STRING_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)ft_string $(BLUE)functions$(NC)\n"
	$(COMPILE)

ft_utils: $(OBJ_DIR) $(FT_UTILS_OBJS)
$(FT_UTILS_OBJS): $(FT_UTILS_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)ft_utils $(BLUE)functions$(NC)\n"
	$(COMPILE)

ft_lst: ft_string $(OBJ_DIR) $(FT_LST_OBJS)
$(FT_LST_OBJS): $(FT_LST_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)ft_lst $(BLUE)functions$(NC)\n"
	$(COMPILE)

ft_idllst: ft_string $(OBJ_DIR) $(FT_IDLLST_OBJS)
$(FT_IDLLST_OBJS): $(FT_IDLLST_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)ft_idllst $(BLUE)functions$(NC)\n"
	$(COMPILE)

ft_io: ft_utils ft_string $(OBJ_DIR) $(FT_IO_OBJS)
$(FT_IO_OBJS): $(FT_IO_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)ft_io $(BLUE)functions$(NC)\n"
	$(COMPILE)

ft_to: ft_utils ft_ctype ft_string $(OBJ_DIR) $(FT_TO_OBJS)
$(FT_TO_OBJS): $(FT_TO_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)ft_io $(BLUE)functions$(NC)\n"
	$(COMPILE)

get_next_line: ft_string $(OBJ_DIR) $(GNL_OBJS)
$(GNL_OBJS): $(GNL_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)ft_io $(BLUE)functions$(NC)\n"
	$(COMPILE)


no_opti: OPTI =
no_opti: debug

debug: CFLAGS = -g 
debug: all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.SILENT:

###############################################################################
## 								Norm recipe									 ##
###############################################################################

norm:
	printf "$(BLUE)Checking norm$(NC)\n"
	norminette $(LIBS_SRCS) $(addprefix $(INC_DIR)/, $(HEADERS))\
	; if [ "$$?" -ne "0" ]; then printf "$(RED)NORM ERROR$(NC)\n"; \
	else printf "$(GREEN)NORM OK$(NC)\n";fi
