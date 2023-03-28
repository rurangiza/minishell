# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:47:23 by arurangi          #+#    #+#              #
#    Updated: 2023/03/28 14:54:42 by arurangi         ###   ########.fr        #
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
					srcs/signals.c \
					srcs/debug.c \
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

# Only execute the line if the current user is "johndoe"
ifeq ($(CURRENT_USER),akorompa)
	READLINE_LIB = -lreadline -lhistory -L /Users/akorompa/.brew/opt/readline/lib
	READLINE_INC = -I /Users/akorompa/.brew/opt/readline/include
else
	READLINE_LIB = -lreadline -lhistory -L /Users/arurangi/.brew/opt/readline/lib
	READLINE_INC = -I /Users/arurangi/.brew/opt/readline/include
endif

%.o: %.c
	$(CC) -Wall -Wextra -Werror -fsanitize=address -g -I ${INCLUDES} $(READLINE_INC) -c $< -o $@

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

.PHONY:			all clean fclean re