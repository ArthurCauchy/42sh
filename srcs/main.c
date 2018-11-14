/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/14 12:26:29 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "builtins.h"
#include "history.h"
#include "init.h"
#include "line_edit.h"
#include "parsing.h"
#include "interpreter.h"
#include "redirects.h"
#include "heredoc.h"

t_env		*g_env = NULL;
t_history	*g_history = NULL;
int			g_with_termcap = 0;
int			g_last_command_status = 0;
t_alias		*g_aliases = NULL;
int			g_winsize_changed = 0;
pid_t		g_shell_pid = -1;
int			g_termcap_enabled = 0;
t_termios	g_old_termios;

static int	input_ask(int lex_ret, char **tmp, t_word **cmd_args, char **input)
{
	if (lex_ret == 1)
		*tmp = ask_for_input(SQUOTE_PROMPT, NULL);
	else if (lex_ret == 2)
		*tmp = ask_for_input(DQUOTE_PROMPT, NULL);
	else
		*tmp = ask_for_input(SLASH_PROMPT, NULL);
	if (*tmp == NULL)
	{
		delete_wordlist(cmd_args);
		return (1);
	}
	if (lex_ret == 1 || lex_ret == 2)
	{
		*input = ft_strjoin_free(
				ft_strjoin_free(*input, ft_strdup("\n")),
				*tmp);
	}
	else
		*input = ft_strjoin_free(*input, *tmp);
	return (0);
}

static int	input_lexing(char **input, t_word **cmd_args)
{
	int				lex_ret;
	char			*tmp;

	while ((lex_ret = lex_analysis(input, cmd_args, NULL)) != 0)
	{
		delete_wordlist(cmd_args);
		if (input_ask(lex_ret, &tmp, cmd_args, input))
			return (1);
		exc_mark(input);
	}
	return (0);
}

static void	main_loop(char **input)
{
	char			*errmsg;
	t_word			*cmd_args;
	t_parse_block	*parsed;

	errmsg = NULL;
	cmd_args = NULL;
	parsed = NULL;
	exc_mark(input);
	if (input_lexing(input, &cmd_args) == 1)
		return ;
	if (apply_heredocs(cmd_args, &errmsg) == -1)
	{
		if (errmsg)
			print_n_free_errmsg(&errmsg);
		clear_heredocs_fds();
		g_last_command_status = 1;
	}
	else if (cmd_args)
		main_parsing(&cmd_args, &parsed, &errmsg, input);
	delete_wordlist(&cmd_args);
}

void		recursive_main_loop(char **input)
{
	char *tmp;
	char *new;
	char *space;

	tmp = ask_for_input(SLASH_PROMPT, NULL);
	if (tmp != NULL)
	{
		if (ft_strcmp(tmp, "") != 0)
			space = ft_strjoin(*input, " ");
		else
			space = ft_strdup(*input);
		new = ft_strjoin(space, tmp);
		free(space);
		free(tmp);
		if (ft_strlen(new) < INPUT_MAX_LEN - 1)
			main_loop(&new);
		else
			ft_putstr_fd("Command too long.\n", 2);
		free(new);
	}
}

int			main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	input = NULL;
	init(&g_env, envp);
	while ((input = ask_for_input(NORMAL_PROMPT, NULL)) != NULL)
	{
		main_loop(&input);
		free(input);
	}
	return (0);
}
