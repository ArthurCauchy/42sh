/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/05 20:28:23 by arthur           ###   ########.fr       */
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

t_env		*g_env = NULL;
t_history	*g_history = NULL;
int			g_with_termcap = 0;
int			g_last_command_status = 0;
t_alias		*g_aliases = NULL;
int			g_winsize_changed = 0;
pid_t		g_shell_pid = -1;

static void	main_loop(char **input)
{
	char			*errmsg;
	t_word			*cmd_args;
	t_parse_block	*parsed;
	int				ret;
	int				lex_ret;

	errmsg = NULL;
	cmd_args = NULL;
	parsed = NULL;
	exc_mark(input);
	while ((lex_ret = lex_analysis(input, &cmd_args, NULL)) != 0) // this while block should become a function
	{
		char *tmp;

		delete_wordlist(&cmd_args);
		if (lex_ret == 1)
			tmp = ask_for_input(SQUOTE_PROMPT);
		else if (lex_ret == 2)
			tmp = ask_for_input(DQUOTE_PROMPT);
		else
			tmp = ask_for_input(SLASH_PROMPT);
		if (tmp == NULL)
		{
			delete_wordlist(&cmd_args);
			return ;
		}
		*input = ft_strjoin_free(
			ft_strjoin_free(*input, ft_strdup("\n")),
			tmp);
		// TODO check command too long !!!
	}
	history_add(*input);
	if (cmd_args)
	{
		//0 = SUCCES;
		//-1 = INVALID;
		//1 = UNFINISHED;
		if ((ret = do_parsing(cmd_args, &parsed, &errmsg)) == 0)
			g_last_command_status = do_interpret(&g_env, parsed);
		else if (ret == 1)
		{
			char *tmp;
			char *new;

			tmp = ask_for_input(SLASH_PROMPT);
			new = ft_strjoin(*input, tmp);
			free(tmp);
			if (ft_strlen(new) < INPUT_MAX_LEN - 1)
				main_loop(&new);
			else
				ft_putstr_fd("Command too long.\n", 2);
			free(new);
		}
		else
			g_last_command_status = 1;
		free_parse_block(&parsed);
		delete_wordlist(&cmd_args);
	}
}

int			main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	init(&g_env, envp);
	while ((input = ask_for_input(NORMAL_PROMPT)) != NULL)
	{
		main_loop(&input);
		free(input);
	}
	return (0);
}
