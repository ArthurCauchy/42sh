/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/01 14:33:54 by arthur           ###   ########.fr       */
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
pid_t		g_shell_pid;

static void	main_loop(char *input)
{
	char			*errmsg;
	t_word			*cmd_args;
	t_parse_block	*parsed;
	
	errmsg = NULL;
	cmd_args = NULL;
	exc_mark(&input);
	lex_analysis(&input, &cmd_args, NULL);
	history_add(input);
	if (cmd_args)
	{
		parsed = do_parsing(cmd_args, &errmsg);
		if (!parsed)
			g_last_command_status = 1;
		else
			g_last_command_status = do_interpret(&g_env, parsed);
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
		main_loop(input);
		free(input);
	}
	return (0);
}
