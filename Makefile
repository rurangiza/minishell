# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 13:20:22 by arurangi          #+#    #+#              #
#    Updated: 2023/01/23 13:21:47 by arurangi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= 	srcs/main.c \

INCLUDES		= includes/minishell.h

OBJS	= ${SRCS:.c=.o}

NAME 	= minishell

LIBFT = libft

CC			= gcc
CCFLAGS 	= -Wall -Wextra -Werror -lreadline

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I ${INCLUDES} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS} ${INCLUDES}
			$(CC) $(CCFLAGS) -o $(NAME) $(OBJS)
#$(CC) $(CCFLAGS) -L ./libft -l ft -o $(NAME) $(OBJS)
#make -C $(LIBFT)

clean:
				rm -f ${OBJS}
				make clean -C $(LIBFT)

fclean: 	clean
				rm -f ${NAME}
				make fclean -C $(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re