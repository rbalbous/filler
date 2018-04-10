# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/15 22:03:07 by rbalbous          #+#    #+#              #
#    Updated: 2018/04/10 17:04:10 by rbalbous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = 		ft_strcat.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c \
			ft_strncat.c ft_strncpy.c ft_tolower.c ft_toupper.c \
			ft_bzero.c ft_atoi.c ft_strcmp.c ft_strchr.c ft_strrchr.c \
			ft_strstr.c ft_strnstr.c ft_strnew.c ft_strdel.c ft_strclr.c \
			ft_strequ.c ft_strnequ.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c \
			ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memdel.c \
			ft_memalloc.c ft_putchar.c ft_putnbr.c ft_putstr.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_strjoin.c ft_strtrim.c ft_memmove.c \
			ft_strncmp.c ft_memcmp.c ft_strsub.c ft_strsplit.c ft_striter.c \
			ft_striteri.c ft_strmap.c ft_strmapi.c ft_itoa.c ft_lstmap.c \
			ft_lstiter.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstnew.c \
			ft_lstaddlast.c ft_strjoinfree.c ft_max.c ft_min.c ft_memacpy.c \
			ft_sort_int.c ft_puterror.c ft_countwords.c ft_putitab.c \
			ft_putstab.c ft_tablen.c ft_intlen.c ft_strsplitfree.c get_next_line.c \
			ft_strnchr.c ft_abs.c
LIB_PATH = basic
OBJ += $(addprefix $(OBJ_PATH)/, $(LIB:.c=.o))

$(OBJ_PATH)/%.o : $(LIB_PATH)/%.c $(INCLUDES)/ft_printf.h
	@$(CC) -o $@ -c $< -I $(INCLUDES) $(CFLAGS)
