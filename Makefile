# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 15:23:24 by rbalbous          #+#    #+#              #
#    Updated: 2018/04/07 18:40:34 by rbalbous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rbalbous.filler

VISU = visu

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

SRCS =	main.c \
		filler.c \
		map.c \
		piece.c \
		filler_init.c \
		filler_algo.c \
		update_map.c
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
			@$(CC) -o $@ $^ $(FLAGS)
			@echo "\033[32mfiller done\033[m"

$(VISU) :	$(LIB) $(VISU_OBJ)
			@$(CC) -o $@ $^ $(FLAGS) -L ~/.brew/lib/ -lsdl2 -lsdl2_ttf -I ~/.brew/include/SDL2
			@echo "\033[35mvisu done\033[m"

$(LIB) :
			@make -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES)/filler.h
			@mkdir -p $(OBJ_PATH)
			@$(CC) -o $@ -c $< -I $(INCLUDES) -I $(LIB_PATH)/includes -I $(FLAGS) -I ~/.brew/include/SDL2

clean :
			@make -C $(LIB_PATH) clean
			@rm -f $(OBJ)
			@rm -f $(VISU_OBJ)

fclean :	clean
			@rm -f $(NAME)
			@rm -f $(VISU)
			@rm -f $(LIB)

re : fclean 
			@make

.PHONY : all clean fclean re
