# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 15:10:49 by jberredj          #+#    #+#              #
#    Updated: 2021/11/04 18:12:51 by jberredj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	clang
OPTI			=	-O2
CFLAGS			=	-Wall -Werror -Wextra $(OPTI)
LDFLAGS			=	-Llibft -lreadline

CODE_VERSION	=	-D VERSION_NUMBER=\"`git log -1 --pretty=format:'%h'`\"

SRC_DIR			= 	srcs
INC_DIR			=	includes
OBJ_DIR			=	objs

LIBS			=	libft.a

###############################################################################
##								Source files								 ##
###############################################################################

MAIN			=	main.c environement/env.c

SRCS			=	$(addprefix srcs/, $(MAIN)) \

STRUCTS			=	
HEADERS			=	

OBJS			=	$(addprefix objs/, $(notdir $(SRCS:.c=.o)))

###############################################################################
##							Color output char								 ##
###############################################################################
BLUE			=\033[0;34m
NC				=\033[0m
LIGHT_PURPLE	=\033[1;35m
GREEN			=\033[0;32m
RED				=\033[0;31m

###############################################################################
## 							Mandatory recipes								 ##
###############################################################################

all: $(NAME)

$(NAME): $(LIBS) $(OBJ_DIR) $(OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$(NAME) $(BLUE)executable$(NC)\n"
	$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)
	printf "$(GREEN)Completed$(NC)\n"

clean:
	printf "$(RED)Removing objects files$(NC)\n"
	rm -rf objs
	rm -rf *.o;

fclean: clean
	printf "$(RED)Removing $(LIGHT_PURPLE)$(NAME) \
	$(RED)executable\nRemoving libraries$(NC)\n"	
	rm -rf $(NAME)
	rm -rf $(LIBS)

re: fclean all

###############################################################################
## 								Extra recipes								 ##
###############################################################################

ffclean: fclean
	make -C libft fclean

$(OBJS): $(SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)$(NAME) $(BLUE)sources$(NC)\n"
	find ./objs/ -type f -exec touch {} +
	$(foreach source,$?, \
	$(CC) -I $(INC_DIR) $(CFLAGS) $(CODE_VERSION) -c $(source);printf "Compiling $(LIGHT_PURPLE) \
	$(notdir $(source) $(NC)\n");)
	mv -f $(notdir $(?:.c=.o)) objs/

$(SRCS): $(addprefix $(INC_DIR)/, $(HEADERS))
 
libft.a:
	make -C libft 
	cp libft/libft.a .

no_opti: OPTI =
no_opti: debug

debug: CFLAGS = -g -D DEBUG 
debug: all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

valgrind:
	valgrind --suppressions=./ignoreliberror --leak-check=full ./$(NAME)

.SILENT:

###############################################################################
## 								Norm recipe									 ##
###############################################################################

norm:
	printf "$(BLUE)Checking norm$(NC)\n"
#		   Removing mlx.h, because it's not normed and cause norminette to fail
#												↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	norminette $(SRCS) $(addprefix $(INC_DIR)/, $(filter-out mlx.h, $(HEADERS))) \
	libs/libft ; if [ "$$?" -ne "0" ]; then printf "$(RED)NORM ERROR$(NC)\n"; \
	else printf "$(GREEN)NORM OK$(NC)\n";fi