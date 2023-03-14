# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:47:23 by arurangi          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/03/10 10:29:01 by akorompa         ###   ########.fr        #
=======
#    Updated: 2023/03/13 15:30:45 by arurangi         ###   ########.fr        #
>>>>>>> 8531c8f7d370da792b45aeb2f875252c5084b7a5
#                                                                              #
# **************************************************************************** #

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

READLINE_LIB = -lreadline -lhistory -L /Users/akorompa/.brew/opt/readline/lib
READLINE_INC = -I /Users/akorompa/.brew/opt/readline/include

%.o: %.c
	$(CC) -Wall -Wextra -Werror -fsanitize=address -g -I ${INCLUDES} $(READLINE_INC) -c $< -o $@

all:		${NAME}
			./minishell

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