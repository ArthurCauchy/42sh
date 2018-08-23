# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 10:04:49 by acauchy           #+#    #+#              #
#    Updated: 2018/08/23 11:53:03 by arthur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL:=/bin/bash
UNAME_S := $(shell uname -s)

.PHONY: all clean fclean re compile

COLOR_GREEN = "\033[1;32;40m"
COLOR_RED = "\033[1;31;40m"
COLOR_YELLOW = "\033[1;33;40m"
COLOR_CYAN = "\033[1;36;40m"
COLOR_RESET = "\033[0m"

NAME = 42sh

CC = gcc -g3
CFLAGS = -Wall -Wextra -Werror

HEADER_PATH = headers
HEADER_NAME = utils.h \
			  env.h \
			  path.h \
			  builtins.h \
			  lexing.h \
			  init.h
HEADER = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

SRC_PATH = srcs
SRC_NAME = utils.c \
		   utils2.c \
		   utils_args.c \
		   s_env.c \
		   env.c \
		   path.c \
		   builtins_manager.c \
		   builtins_utils.c \
		   builtin_exit.c \
		   builtin_cd.c \
		   builtin_cd_l.c \
		   builtin_cd_l_component.c \
		   builtin_cd_l_simplify.c \
		   builtin_cd_p.c \
		   builtin_env.c \
		   builtin_setenv.c \
		   builtin_unsetenv.c \
		   builtin_echo.c \
		   builtin_which.c \
		   init.c \
		   init_builtins.c \
		   init_env.c \
		   word.c \
		   lexing.c \
		   lexing_dollar.c \
		   lexing_tilde.c \
		   lexing_semicol.c \
		   lexing_pipe_or.c \
		   lexing_amp_and.c \
		   lexing_shift.c \
		   lexing_lshift.c \
		   lexing_rshift.c \
		   lexing_space.c \
		   main.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH = libft
LIBFT_INCLUDE = -I$(LIBFT_PATH)
LIBFT = -L$(LIBFT_PATH) -lft

LIBTERMCAP = -ltermcap

LIBCURSES = -lcurses

all: compile

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	$(CC) -c -o $@ $(CFLAGS) $< $(LIBFT_INCLUDE) -I$(HEADER_PATH)

$(NAME): $(OBJ)
	@echo -e $(COLOR_YELLOW)"Linking "$@"..."$(COLOR_RESET)
	$(CC) $^ $(LIBCURSES) $(LIBTERMCAP) $(LIBFT) -o $@
	@echo -e $(COLOR_GREEN)$(NAME)" successfully created."$(COLOR_RESET)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

compile: $(OBJ_PATH)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH)
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@echo -e $(COLOR_YELLOW)"Compiling "$(NAME)"..."$(COLOR_RESET)
	@make $(NAME)

clean:
	@echo -e $(COLOR_RED)"Removing "$(OBJ_PATH)"..."$(COLOR_RESET)
	rm -Rf $(OBJ_PATH)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH) clean
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFT_PATH)"=="$(COLOR_RESET)

fclean: clean
	@echo -e $(COLOR_RED)"Removing "$(NAME)"..."$(COLOR_RESET)
	rm -f $(NAME)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH) fclean
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFT_PATH)"=="$(COLOR_RESET)

re: fclean all
