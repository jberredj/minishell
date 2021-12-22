# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 17:39:23 by jberredj          #+#    #+#              #
#    Updated: 2021/12/22 13:20:26 by jberredj         ###   ########.fr        #
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
OBJ_DIR			=	objs/

LIBS			=	libft.a

###############################################################################
##								Source files								 ##
###############################################################################

BUILTIN			= 	builtin_selector.c cd.c cd_utils.c echo.c placeholder.c \
					exit.c pwd.c env.c
BUILTIN_SRCS	=	$(addprefix srcs/builtin/, $(BUILTIN))
BUILTIN_OBJS	=	$(addprefix objs/builtin., $(subst /,., $(BUILTIN:.c=.o)))

ENV				=	envp/free.c envp/update.c envp/utils.c\
					var/create.c var/free.c var/update.c var/utils.c \
					env_var_to_envp.c parse_herited.c
ENV_SRCS		=	$(addprefix srcs/env/, $(ENV))
ENV_OBJS		=	$(addprefix objs/env., $(subst /,., $(ENV:.c=.o)))

EXEC			=	builtin.c exec.c external.c utils.c signals.c \
					errors/builtin.c errors/external.c errors/exec.c \
					redirections/redirect_files.c redirections/pipes.c \
					redirections/treat_redirections.c
EXEC_SRCS		=	$(addprefix srcs/exec/, $(EXEC))
EXEC_OBJS		=	$(addprefix objs/exec., $(subst /,., $(EXEC:.c=.o)))

EXPANDER		=	expand_var.c get_var_len.c get_words_len.c special_case.c \
					substitute.c
EXPANDER_SRCS	=	$(addprefix srcs/expander/, $(EXPANDER))
EXPANDER_OBJS	=	$(addprefix objs/expander., $(subst /,., $(EXPANDER:.c=.o)))

PARSER			=	check_command_path.c create.c free.c set_argv.c \
					tokens_to_commands.c heredoc.c pipes.c redirect_files.c 
PARSER_SRCS		=	$(addprefix srcs/parser/, $(PARSER))
PARSER_OBJS		=	$(addprefix objs/parser., $(subst /,., $(PARSER:.c=.o)))

PROMPT			=	prompt.c prompt_text.c
PROMPT_SRCS		=	$(addprefix srcs/prompt/, $(PROMPT))
PROMPT_OBJS		=	$(addprefix objs/prompt., $(subst /,., $(PROMPT:.c=.o)))

TOKENISER		= 	copy_content.c free.c quote.c separator.c tokenise_line.c word.c
TOKENISER_SRCS	=	$(addprefix srcs/tokeniser/, $(TOKENISER))
TOKENISER_OBJS	=	$(addprefix objs/tokeniser.,\
						$(subst /,., $(TOKENISER:.c=.o)))

MAIN			=	main.c _debug.c
MAIN_SRCS		=	$(addprefix srcs/, $(MAIN))
MAIN_OBJS		=	$(addprefix objs/, $(subst /,., $(MAIN:.c=.o)))


STRUCTS			=	t_command.h t_env.h t_token.h
HEADERS			=	$(addprefix structs/, $(STRUCTS))\
					builtin.h env.h error_codes.h minishell.h parser.h\
					prompt.h tokeniser.h expander.h

SRCS			=	$(EXPANDER_SRCS) $(BUILTIN_SRCS) $(ENV_SRCS) $(EXEC_SRCS) $(PARSER_SRCS) $(PROMPT_SRCS)\
					$(TOKENISER_SRCS) $(MAIN_SRCS)
OBJS			=	$(EXPANDER_OBJS) $(BUILTIN_OBJS) $(ENV_OBJS) $(EXEC_OBJS) $(PARSER_OBJS) $(PROMPT_OBJS)\
					$(TOKENISER_OBJS) $(MAIN_OBJS)

MODULE			=	expander builtin env exec parser prompt tokeniser main

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

$(NAME): $(OBJ_DIR) $(LIBS) $(OBJS)
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

define COMPILE
	find ./objs/ -type f -exec touch {} +
	$(foreach source,$?, \
	printf "$(YELLOW)[..]   $(NC) $(LIGHT_PURPLE)$(subst srcs/,,$(source))\
$(NC)\n"; \
	$(CC) -I $(INC_DIR) $(CFLAGS) $(CODE_VERSION) -c $(source) -o \
$(addprefix $(OBJ_DIR), $(subst /,.,$(subst srcs/,,$(source:.c=.o)))) ; \
	if [ $$? -ne "0" ];\
	then \
		exit 1;\
	fi; \
	norminette $(source) > /dev/null ;\
	if [ $$? -ne "0" ];\
	then \
		printf "\033[F$(RED)[NORM]$(NC) $(LIGHT_PURPLE)\
$(subst srcs/,,$(source))$(NC)\n";\
	else \
		printf "\033[F$(GREEN)[OK]  $(NC) $(LIGHT_PURPLE)\
$(subst srcs/,,$(source))$(NC)\n";\
	fi;)
endef

builtin: $(OBJ_DIR) $(BUILTIN_OBJS)
$(BUILTIN_OBJS): $(BUILTIN_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)builtin $(BLUE)functions$(NC)\n"
	$(COMPILE)

env: $(OBJ_DIR) $(ENV_OBJS)
$(ENV_OBJS): $(ENV_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)environement $(BLUE)\
functions$(NC)\n"
	$(COMPILE)

exec: $(OBJ_DIR) $(EXEC_OBJS)
$(EXEC_OBJS): $(EXEC_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)executer $(BLUE)\
functions$(NC)\n"
	$(COMPILE)

expander: $(OBJ_DIR) $(EXPANDER_OBJS)
$(EXPANDER_OBJS): $(EXPANDER_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)expander $(BLUE)functions$(NC)\n"
	$(COMPILE)

parser: $(OBJ_DIR) $(PARSER_OBJS)
$(PARSER_OBJS): $(PARSER_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)parser $(BLUE)functions$(NC)\n"
	$(COMPILE)

prompt: $(OBJ_DIR) $(PROMPT_OBJS)
$(PROMPT_OBJS): $(PROMPT_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)prompt $(BLUE)functions$(NC)\n"
	$(COMPILE)

tokeniser: $(OBJ_DIR) $(TOKENISER_OBJS)
$(TOKENISER_OBJS): $(TOKENISER_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)tokeniser $(BLUE)functions$(NC)\n"
	$(COMPILE)

main: $(OBJ_DIR) $(MAIN_OBJS)
$(MAIN_OBJS): $(MAIN_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)main $(BLUE)functions$(NC)\n"
	$(COMPILE)

ffclean: fclean
	make -C libft fclean

$(SRCS): $(addprefix $(INC_DIR)/, $(HEADERS))
 
libft.a:
	make -C libft 
	cp libft/libft.a .

debug: CFLAGS = -g -D DEBUG 
debug: all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

valgrind:
	valgrind  --trace-children=yes --suppressions=./ignoreliberror  --leak-check=full --show-leak-kinds=all ./$(NAME)

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
