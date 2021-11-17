# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 15:10:49 by jberredj          #+#    #+#              #
#    Updated: 2021/11/17 10:29:46 by jberredj         ###   ########.fr        #
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

ENV				=	var/create.c var/free.c var/update.c var/utils.c env.c \
					parse_herited.c

MAIN			=	main.c 



STRUCTS			=	
HEADERS			=

SRCS			=	$(addprefix srcs/, $(MAIN)) \
					$(addprefix srcs/env/, $(ENV))
OBJS			=	$(addprefix objs/, $(subst /,., $(subst srcs/,, $(SRCS:.c=.o))))

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

define COMPILE =
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

ffclean: fclean
	make -C libft fclean

$(OBJS): $(SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)$(NAME) $(BLUE)sources$(NC)\n"
	$(COMPILE)

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

commit_all_files: ffclean
	git add .
	git commit

###############################################################################
## 								Norm recipe									 ##
###############################################################################

norm:
	printf "$(BLUE)Checking norm$(NC)\n"
	norminette $(SRCS) $(addprefix $(INC_DIR)/, $(HEADERS)) \
	libft ; if [ "$$?" -ne "0" ]; then printf "$(RED)NORM ERROR$(NC)\n"; \
	else printf "$(GREEN)NORM OK$(NC)\n";fi