# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 15:24:07 by arurangi          #+#    #+#              #
#    Updated: 2023/01/24 15:08:39 by arurangi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROGRAM
NAME	=	minishell
LIBFT	=	./src/library/libft.a

# DERECTORIES
LIBFT_DIR	=	./src/library/
SRC_DIR		=	./src/
BONUS_DIR	=	./src/bonus/

# SOURCE FILES
SOURCE_FILES	=	${SRC_DIR}main.c \
					${SRC_DIR}parsing.c \
					${SRC_DIR}processes.c \
					${SRC_DIR}init.c \
					${SRC_DIR}errors.c \
					${SRC_DIR}expander.c \
					src/built-ins/echo.c \
					

# VARIABLES
COMPILER	= 	gcc
C_FLAGS		=	-Wall -Wextra -Werror
rm			=	rm -f

OBJ			=	${SOURCE_FILES:.c=.o}
OBJB		=	${BONUS_FILES:.c=.o}

# RULES
%.o: 		%.c
				$(COMPILER) $(C_FLAGS) -c $< -o $@

$(NAME): 	$(OBJ) $(LIBFT)
				$(COMPILER) $(C_FLAGS) -lreadline $(OBJ) $(LIBFT_DIR)libft.a -o ${NAME}

$(LIBFT):
				make -C $(LIBFT_DIR)

all:		$(NAME)

clean:
				make -C $(LIBFT_DIR) fclean
				rm -f $(OBJ) core
				rm -f $(OBJB) core

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

bonus:		${OBJB} $(LIBFT)
			$(COMPILER) $(OBJB) $(LIBFT_DIR)libft.a -o $(NAME)

.PHONY:		all clean fclean re bonus