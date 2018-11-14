# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 10:04:49 by acauchy           #+#    #+#              #
#    Updated: 2018/11/14 11:39:17 by saxiao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL:=/bin/bash

.PHONY: all clean fclean re compile

COLOR_GREEN = "\033[1;32;40m"
COLOR_RED = "\033[1;31;40m"
COLOR_YELLOW = "\033[1;33;40m"
COLOR_CYAN = "\033[1;36;40m"
COLOR_RESET = "\033[0m"

NAME = 42sh

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror

HEADER_PATH = headers
HEADER_NAME = utils.h \
			  env.h \
			  path.h \
			  builtins.h \
			  lexing.h \
			  parsing.h \
			  interpreter.h \
			  starter.h \
			  redirects.h \
			  heredoc.h \
			  init.h \
			  global.h \
			  history.h \
			  line_edit.h \
			  colors.h \
			  exc_mark.h
HEADER = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

SRC_PATH = srcs
SRC_NAME = utils.c \
		   utils2.c \
		   utils_args.c \
		   utils_signals.c \
		   utils_process.c \
		   utils_vars.c \
		   s_env.c \
		   env.c \
		   path.c \
		   builtins_manager.c \
		   builtins_utils.c \
		   builtin_exit.c \
		   builtin_cd.c \
		   builtin_cd_cdpath.c \
		   builtin_cd_l.c \
		   builtin_cd_l_component.c \
		   builtin_cd_l_simplify.c \
		   builtin_cd_p.c \
		   builtin_env.c \
		   builtin_setenv.c \
		   builtin_unsetenv.c \
		   builtin_echo.c \
		   builtin_which.c \
		   builtin_help.c \
		   builtin_history.c \
		   builtin_history_error.c \
		   builtin_history_helper.c \
		   builtin_history_messages.c \
		   builtin_history_options.c \
		   builtin_alias.c \
		   builtin_unalias.c \
		   init.c \
		   init_signals.c \
		   init_env.c \
		   init_builtins.c \
		   init_termios.c \
		   init_history.c \
		   word.c \
		   lexing.c \
		   lexing_escape.c \
		   lexing_tilde.c \
		   lexing_semicol.c \
		   lexing_pipe_or.c \
		   lexing_amp_and.c \
		   lexing_shift.c \
		   lexing_lshift.c \
		   lexing_rshift.c \
		   lexing_space.c \
		   parse_block.c \
		   parse_block_clone.c \
		   parsing.c \
		   parsing_error.c \
		   interpreter.c \
		   interpreter_run.c \
		   process.c \
		   starter.c \
		   starter_forked.c \
		   redirects.c \
		   redirections.c \
		   redirections_fdsave.c \
		   redirections_apply.c \
		   redirections_apply_pipe.c \
		   redirections_apply_rshift.c \
		   redirections_apply_rshift2.c \
		   redirections_apply_rshift_amp.c \
		   redirections_apply_lshift.c \
		   redirections_apply_lshift2.c \
		   redirections_apply_lshift_amp.c \
		   heredoc.c \
		   heredoc_db.c \
		   history_tools.c \
		   history_init.c \
		   history_helper.c \
		   history.c \
		   exc_mark.c \
		   exc_mark_fill.c \
		   exc_mark_get.c \
		   exc_mark_tools.c \
		   exc_mark_return.c \
		   line_termcap_setting.c \
		   line_engine.c \
		   line_mv_right.c \
		   line_mv_left.c \
		   line_delete.c \
		   line_printable.c \
		   line_his_up_down.c \
		   line_cp_cut.c \
		   line_paste_go_updown.c \
		   line_ctrl_d.c \
		   line_helper.c \
		   line_get_line.c \
		   line_my_free.c \
		   line_sort_list.c \
		   line_auto_color.c \
		   line_input.c \
		   line_clscreen_winchangesize.c \
		   auto_key_isarrow.c \
		   auto_start_current.c \
		   auto_add_a_list_nbuildin.c \
		   auto_get_autolist.c \
		   auto_put_colum.c \
		   auto_calcu.c \
		   auto_return_key.c \
		   auto_put_choice.c \
		   auto_my_tabkey.c \
		   auto_help.c \
		   main.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH = libft
LIBFT_INCLUDE = -I$(LIBFT_PATH)
LIBFT = -L$(LIBFT_PATH) -lft

LIBFTPRINTF_PATH = libft/ft_printf
LIBFTPRINTF_INCLUDE = -I$(LIBFTPRINTF_PATH)/includes
LIBFTPRINTF = -L$(LIBFTPRINTF_PATH) -lftprintf

LIBTERMCAP = -ltermcap

all: compile

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	$(CC) -c -o $@ $(CFLAGS) $< $(LIBFT_INCLUDE) $(LIBFTPRINTF_INCLUDE) -I$(HEADER_PATH)

$(NAME): $(OBJ)
	@echo -e $(COLOR_YELLOW)"Linking "$@"..."$(COLOR_RESET)
	$(CC) $^ $(LIBTERMCAP) $(LIBFTPRINTF) $(LIBFT) -o $@
	@echo -e $(COLOR_GREEN)$(NAME)" successfully created."$(COLOR_RESET)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

compile: $(OBJ_PATH)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH)
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFTPRINTF_PATH)"=="$(COLOR_RESET)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFTPRINTF_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFTPRINTF_PATH)
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFTPRINTF_PATH)"=="$(COLOR_RESET)
	@echo -e $(COLOR_YELLOW)"Compiling "$(NAME)"..."$(COLOR_RESET)
	@make $(NAME)

clean:
	@echo -e $(COLOR_RED)"Removing "$(OBJ_PATH)"..."$(COLOR_RESET)
	rm -Rf $(OBJ_PATH)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH) clean
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFTPRINTF_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFTPRINTF_PATH) clean
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFTPRINTF_PATH)"=="$(COLOR_RESET)

fclean: clean
	@echo -e $(COLOR_RED)"Removing "$(NAME)"..."$(COLOR_RESET)
	rm -f $(NAME)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFT_PATH) fclean
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFT_PATH)"=="$(COLOR_RESET)
	@echo -e $(COLOR_CYAN)"==Entering "$(LIBFTPRINTF_PATH)"=="$(COLOR_RESET)
	@make -C $(LIBFTPRINTF_PATH) fclean
	@echo -e $(COLOR_CYAN)"==Exiting "$(LIBFTPRINTF_PATH)"=="$(COLOR_RESET)

re: fclean all
