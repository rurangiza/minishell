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