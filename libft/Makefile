# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 15:57:30 by acauchy           #+#    #+#              #
#    Updated: 2018/06/03 12:54:25 by arthur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL:=/bin/bash

.PHONY: all clean fclean re compile

COLOR_GREEN = "\033[1;32;40m"
COLOR_RED = "\033[1;31;40m"
COLOR_YELLOW = "\033[1;33;40m"
COLOR_CYAN = "\033[1;36;40m"
COLOR_RESET = "\033[0m"

CC = gcc -g3

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC_NAME = ft_memset.c \
		 ft_bzero.c \
		 ft_memcpy.c \
		 ft_memccpy.c \
		 ft_memmove.c \
		 ft_memchr.c \
		 ft_memcmp.c \
		 ft_strlen.c \
		 ft_strdup.c \
		 ft_strdup_free.c \
		 ft_strcpy.c \
		 ft_strncpy.c \
		 ft_strcat.c \
		 ft_strncat.c \
		 ft_strlcat.c \
		 ft_strchr.c \
		 ft_strrchr.c \
		 ft_strstr.c \
		 ft_strnstr.c \
		 ft_strcmp.c \
		 ft_strncmp.c \
		 ft_atoi.c \
		 ft_islower.c \
		 ft_isupper.c \
		 ft_isalpha.c \
		 ft_isspace.c \
		 ft_isdigit.c \
		 ft_isalnum.c \
		 ft_isascii.c \
		 ft_isprint.c \
		 ft_memalloc.c \
		 ft_memdel.c \
		 ft_strnew.c \
		 ft_strdel.c \
		 ft_strclr.c \
		 ft_striter.c \
		 ft_striteri.c \
		 ft_strmap.c \
		 ft_strmapi.c \
		 ft_strequ.c \
		 ft_strnequ.c \
		 ft_strsub.c \
		 ft_strjoin.c \
		 ft_strjoin_free.c \
		 ft_strtrim.c \
		 ft_strsplit.c \
		 ft_strfill_right.c \
		 ft_itoa.c \
		 ft_lltoa.c \
		 ft_toupper.c \
		 ft_tolower.c \
		 ft_putchar.c \
		 ft_putstr.c \
		 ft_putendl.c \
		 ft_putnbr.c \
		 ft_puthex.c \
		 ft_putchar_fd.c \
		 ft_putstr_fd.c \
		 ft_putendl_fd.c \
		 ft_putnbr_fd.c \
		 ft_puthex_fd.c \
		 ft_lstnew.c \
		 ft_lstadd.c \
		 ft_lstpushback.c \
		 ft_lstdelone.c \
		 ft_lstdel.c \
		 ft_lstiter.c \
		 ft_lstmap.c \
		 ft_swap.c \
		 ft_sqrt.c \
		 ft_nbrlen.c \
		 ft_fminiprint.c \
		 ft_printfcts.c \
		 ft_multifree.c \
		 ft_count.c

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))


all: compile

$(OBJ_PATH)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	@echo -e $(COLOR_YELLOW)"Linking "$@"..."$(COLOR_RESET)
	ar rcs $@ $^
	@echo -e $(COLOR_GREEN)$(NAME)" successfully created."$(COLOR_RESET)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

compile: $(OBJ_PATH)
	@echo -e $(COLOR_YELLOW)"Compiling "$(NAME)"..."$(COLOR_RESET)
	@make $(NAME)

clean:
	@echo -e $(COLOR_RED)"Removing "$(OBJ_PATH)"..."$(COLOR_RESET)
	rm -Rf $(OBJ_PATH)

fclean: clean
	@echo -e $(COLOR_RED)"Removing "$(NAME)"..."$(COLOR_RESET)
	rm -Rf $(NAME)

re: fclean all
