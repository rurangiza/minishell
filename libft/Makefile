SRCS =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_strchr.c ft_strdup.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_tolower.c ft_toupper.c \
		ft_putstr_fd.c ft_putchar_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
		ft_strjoin.c ft_substr.c ft_strtrim.c \
		ft_split.c ft_striteri.c ft_strmapi.c ft_itoa.c \
		get_next_line.c get_next_line_utils.c ft_strjoin_mod.c ft_strchr_mod.c \
		ft_lstnew_bonus.c ft_lstlast_bonus.c ft_lstclear_bonus.c ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c ft_lstsize_bonus.c\

BSRCS =	ft_lstnew_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c ft_lstmap_bonus.c \

NAME = libft.a

OBJS = ${SRCS:.c=.o}
BOBJS = ${BSRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror
CC = gcc ${FLAGS}
RM = rm -f

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
#@echo "$(CLR_GREEN).\c$(CLR_RESET)"

all: ${NAME}

${NAME} :   ${OBJS}
	  ar rcs ${NAME} ${OBJS}
	  
bonus: ${OBJS} ${BOBJS}
	ar rcs ${NAME} ${OBJS} ${BOBJS}

clean:
	${RM} ${OBJS} ${BOBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus