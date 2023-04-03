# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:47:23 by arurangi          #+#    #+#              #
#    Updated: 2023/04/03 17:13:37 by arurangi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CURRENT_USER	:=	$(shell whoami)
CURRENT_FOLDER	:=	$(shell pwd)
EXEC_FILE		=	$(CURRENT_FOLDER)/minishell

SRCS			= 	srcs/main.c \
					srcs/parser.c \
					srcs/expander.c \
					srcs/tokens.c \
					srcs/lexer.c \
					srcs/execution.c \
					srcs/process_routines.c \
					srcs/redirection.c \
					srcs/heredoc.c \
					srcs/errors.c \
					srcs/utils.c \
					srcs/checker.c \
					srcs/memory_mgmt.c \
					srcs/initialization.c \
					srcs/error_handling.c \
					srcs/signals.c \
					srcs/debug.c \
					srcs/interface.c \
					srcs/calculator.c \
					srcs/pipeline.c \
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
CCFLAGS 	= -Wall -Wextra -Werror -ggdb3 
SANATIZE	= -g -fsanitize=address

ifeq ($(CURRENT_USER),akorompa)
	READLINE_LIB = -lreadline -lhistory -L /Users/akorompa/.brew/opt/readline/lib
	READLINE_INC = -I /Users/akorompa/.brew/opt/readline/include
else
	READLINE_LIB = -lreadline -lhistory -L /Users/arurangi/.brew/opt/readline/lib
	READLINE_INC = -I /Users/arurangi/.brew/opt/readline/include
endif

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I ${INCLUDES} $(READLINE_INC) -c $< -o $@


all:		${NAME}

${NAME}:	${OBJS} ${INCLUDES}
			make -C $(LIBFT)
			$(CC) $(CCFLAGS) $(READLINE_LIB) -L ./libft -l ft -o $(NAME) $(OBJS)

clean:
				rm -f ${OBJS}
				make clean -C $(LIBFT)

fclean: 	clean
				rm -f ${NAME}
				make fclean -C $(LIBFT)

re:				fclean all

vld:
		@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=definite $(EXEC_FILE)
		
debug:	
		@valgrind --leak-check=full --track-origins=yes --vgdb-error=0 $(EXEC_FILE)
#valgrind --tool=cachegrind --cachegrind-out-file=valgrind.log $(EXEC_FILE)
#cg_annotate valgrind.log
#valgrind --leak-check=full --log-file=valgrind.log $(EXEC_FILE)
#valgrind --leak-check=full $(EXEC_FILE)

.PHONY:			all clean fclean re vld debug