# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 15:24:07 by arurangi          #+#    #+#              #
#    Updated: 2023/02/07 16:30:43 by arurangi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROGRAM
NAME	=	minishell
LIBFT	=	./src/library/libft.a

# DERECTORIES
LIBFT_DIR	=	./src/library/
SRC_DIR		=	./src/
BONUS_DIR	=	./src/bonus/
BUILT_INS	=	./src/built-ins/

# SOURCE FILES
SOURCE_FILES	=	${SRC_DIR}main.c \
					${SRC_DIR}execution.c \
					${SRC_DIR}errors.c \
					${SRC_DIR}utils.c \
					${SRC_DIR}redirections.c \
					${BUILT_INS}echo.c \

# VARIABLES
COMPILER	= 	gcc
C_FLAGS		=	-Wall -Wextra -Werror 
rm			=	rm -f

OBJ			=	${SOURCE_FILES:.c=.o}

# RULES
%.o: 		%.c
				$(COMPILER) $(C_FLAGS) -c $< -o $@

$(NAME): 	$(OBJ) $(LIBFT)
				$(COMPILER) $(C_FLAGS) -lreadline $(OBJ) $(LIBFT_DIR)libft.a -o ${NAME} -g

$(LIBFT):
				make -C $(LIBFT_DIR)

all:		$(NAME)

clean:
				@make -C $(LIBFT_DIR) fclean
				rm -f $(OBJ) core

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re