# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 15:23:24 by rbalbous          #+#    #+#              #
#    Updated: 2018/01/23 16:29:23 by rbalbous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = filler
CC = gcc
FLAGS = -Wall -Wextra -Werror -g

SRCS =	main.c \
		filler.c
SRCS_PATH = srcs
SRC = $(addprefix $(SRCS_PATH)/, $(SRCS))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRCS.c=.o))
OBJ_PATH = obj

INCLUDES = includes/filler.h

LIB_PATH = srcs/lib
LIB = $(LIB_PATH)/libftprintf.a

all :		$(NAME)

$(NAME) :	$(LIB) $(OBJ)
			$(CC) -o $@ $(OBJ) $(FLAGS)

$(LIB) :
			make -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES)/filler.h
			$(CC) -o $@ -c $< -I $(LIB) -I $(INCLUDES) $(FLAGS)

clean :
			make -C $(LIB_PATH) clean
			rm -f $(OBJ)

fclean :	clean
			rm -f $(NAME)
			rm -f $(LIB)

re : fclean all

.PHONY : all clean fclean re
