# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 15:23:24 by rbalbous          #+#    #+#              #
#    Updated: 2018/05/03 13:16:28 by rbalbous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rbalbous.filler

VISU = visu

CC = gcc
FLAGS = -Wall -Wextra -Werror -Ofast

SRCS =	main.c \
		map.c \
		piece.c \
		filler_init.c \
		filler_algo.c \
		update_map.c \
		filler_link.c \
		filler_recur.c \
		filler_territory.c \
		phoney_algo.c
SRCS_PATH = srcs
OBJ = $(addprefix $(OBJ_PATH)/, $(SRCS:.c=.o))
OBJ_PATH = obj

VISU_PATH = srcs
VISU_SRCS = main_visu.c \
			parser_visu.c \
			check_error_visu.c \
			put_visu.c \
			list_visu.c \
			event_visu.c \
			fct_visu.c \
			draw_visu.c
VISU_OBJ = $(addprefix $(OBJ_PATH)/, $(VISU_SRCS:.c=.o))

INCLUDES = includes

LIB_PATH = srcs/libft
LIB = $(LIB_PATH)/libft.a

all :		$(NAME) $(VISU)

$(NAME) :	$(LIB) $(OBJ)
			$(CC) -o $(NAME) $^ $(FLAGS)
			rsync -u $(NAME) resources/players
			@echo "\033[32mfiller done\033[m"

$(VISU) :	$(LIB) $(VISU_OBJ)
			$(CC) -o $@ $^ $(FLAGS) -L ~/.brew/lib/ -lsdl2 -lsdl2_ttf -I ~/.brew/include/SDL2
			@echo "\033[35mvisu done\033[m"

$(LIB) :
			make -j16 -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES)/filler.h
			mkdir -p $(OBJ_PATH)
			$(CC) -o $@ -c $< -I $(INCLUDES) -I $(LIB_PATH)/includes -I $(FLAGS) -I ~/.brew/include/SDL2

clean :
			make -C $(LIB_PATH) clean
			rm -f $(OBJ)
			rm -f $(VISU_OBJ)

fclean :	clean
			rm -f $(NAME)
			rm -f $(VISU)
			rm -f $(LIB)

re : fclean 
			make

.PHONY : all clean fclean re
