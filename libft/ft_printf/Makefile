# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saxiao <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/15 14:39:08 by saxiao            #+#    #+#              #
#    Updated: 2017/12/22 03:37:38 by saxiao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libftprintf.a

C = gcc
CFLAGS = -c -Wall -Wextra -Werror

SRC_NAME = cacul.c con_cp.c con_d.c con_o.c con_s.c con_u.c con_x.c \
		   convert_base.c ft_printf.c put.c set_print_oux.c set_print_d.c \
		   set_castflag.c itoa_max.c itoa_hexbase.c for_print_oux.c ini_set.c
LIB_SCRNAME = ft_atoi.c ft_bzero.c ft_itoa.c ft_putchar.c ft_putstr.c\
			  ft_strchr.c ft_strlen.c ft_memset.c ft_strdup.c
SRC_PATH = srcs/
LIB_PATH = ../
LIB_INC = -I..
LIB_OBJS = $(LIB_SCRNAME:.c=.o)
FT_OBJS = $(SRC_NAME:.c=.o)
OBJS = $(LIB_OBJS) $(FT_OBJS)
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
LIB_SRC = $(addprefix $(LIB_PATH), $(LIB_SCRNAME))
INCLUDE = -I includes

all: $(NAME)

$(NAME):$(OBJS) #$(INCLUDE)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJS):$(SRC)
	$(C) $(CFLAGS) $(LIB_INC) $(LIB_SRC)
	$(C) $(CFLAGS) $(INCLUDE) $(SRC)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
