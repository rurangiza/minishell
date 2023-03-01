# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:47:23 by arurangi          #+#    #+#              #
#    Updated: 2023/03/01 14:11:06 by akorompa         ###   ########.fr        #
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

INCLUDES		= includes/minishell.h

OBJS	= ${SRCS:.c=.o}

NAME 	= minishell

LIBFT = libft

CC			= gcc
CCFLAGS 	= -Wall -Wextra -Werror -lreadline -g -fsanitize=address

%.o: %.c
	$(CC) -Wall -Wextra -Werror -fsanitize=address -g -I ${INCLUDES} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS} ${INCLUDES}
			make -C $(LIBFT)
			$(CC) $(CCFLAGS) -L ./libft -l ft -o $(NAME) $(OBJS)

clean:
				rm -f ${OBJS}
				make clean -C $(LIBFT)

fclean: 	clean
				rm -f ${NAME}
				make fclean -C $(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re