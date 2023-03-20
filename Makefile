# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:47:23 by arurangi          #+#    #+#              #
#    Updated: 2023/03/20 14:22:30 by arurangi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CURRENT_USER	:=	$(shell whoami)

SRCS			= 	srcs/main.c \
					srcs/parser.c \
					srcs/expander.c \
					srcs/tokens.c \
					srcs/lexer.c \
					srcs/execution.c \
					srcs/redirection.c \
					srcs/heredoc.c \
					srcs/errors.c \
					srcs/utils.c \
					srcs/checker.c \
					srcs/memory_mgmt.c \
					srcs/initialization.c \
					srcs/error_handling.c \
					built-ins/pwd.c \
					built-ins/env.c \
					built-ins/export.c \
					built-ins/echo.c \
					built-ins/unset.c \
					built-ins/cd.c \
					built-ins/exit.c \

INCLUDES		= includes/minishell.h

OBJS	= ${SRCS:.c=.o}

NAME 	= minishell

LIBFT = libft

CC			= gcc
CCFLAGS 	= -Wall -Wextra -Werror -g -fsanitize=address


COLOR_GRAY = \033[30m
COLOR_CYAN = \033[1;36m
COLOR_RED = \033[0;31m
COLOR_GREEN	= \033[0;32m
COLOR_RESET = \033[0m

# Only execute the line if the current user is "johndoe"
ifeq ($(CURRENT_USER),akorompa)
	READLINE_LIB = -lreadline -lhistory -L /Users/akorompa/.brew/opt/readline/lib
	READLINE_INC = -I /Users/akorompa/.brew/opt/readline/include
else
	READLINE_LIB = -lreadline -lhistory -L /Users/arurangi/.brew/opt/readline/lib
	READLINE_INC = -I /Users/arurangi/.brew/opt/readline/include
endif

TITLE	=	Minishell

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -fsanitize=address -g -I ${INCLUDES} $(READLINE_INC) -c $< -o $@
	@echo "${COLOR_GREEN}.${COLOR_RESET}\c"

all:		${NAME}

$(TITLE):
			@echo "${COLOR_GRAY}\n   Compiling ${NAME}: ${COLOR_RESET}\c"

${NAME}:	$(TITLE) ${OBJS} ${INCLUDES}
			@make -C $(LIBFT)
			@$(CC) $(CCFLAGS) $(READLINE_LIB) -L ./libft -l ft -o $(NAME) $(OBJS)
#			@echo "${COLOR_GREEN}\n${NAME} Successful compilation${COLOR_RESET}"
#			@echo "${COLOR_CYAN}${NAME} ${COLOR_GREEN}${OBJS_DIR} were created${COLOR_RESET}"

clean:
				@rm -f ${OBJS}
				@make clean -C $(LIBFT)
#				@echo "${COLOR_CYAN}${NAME} ${COLOR_RED}${OBJS_DIR} were deleted${COLOR_RESET}"

fclean: 	clean
				@rm -f ${NAME}
				@make fclean -C $(LIBFT)
#				@echo "${COLOR_CYAN}${NAME} ${COLOR_RED}${NAME} was deleted${COLOR_RESET}"

re:				fclean all

.PHONY:			all clean fclean re