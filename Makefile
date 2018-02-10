# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 15:23:24 by rbalbous          #+#    #+#              #
#    Updated: 2018/02/10 16:33:12 by rbalbous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rbalbous.filler
CC = gcc
FLAGS = -Wall -Wextra -Werror -g

SRCS =	main.c \
		filler.c \
		fi_map.c \
		fi_piece.c
SRCS_PATH = srcs
OBJ = $(addprefix $(OBJ_PATH)/, $(SRCS:.c=.o))
OBJ_PATH = obj

INCLUDES = includes

LIB_PATH = srcs/libft
LIB = $(LIB_PATH)/libft.a

all :		$(NAME)

$(NAME) :	$(LIB) $(OBJ)
			$(CC) -o $@ $^ $(FLAGS)

$(LIB) :
			make -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES)/filler.h
			@mkdir $(OBJ_PATH) 2> /dev/null || true
			$(CC) -o $@ -c $< -I $(INCLUDES) -I $(LIB_PATH)/includes $(FLAGS)

clean :
			make -C $(LIB_PATH) clean
			rm -f $(OBJ)

fclean :	clean
			rm -f $(NAME)
			rm -f $(LIB)

re : fclean all

.PHONY : all clean fclean re
