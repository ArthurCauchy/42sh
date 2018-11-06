/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/06 12:13:50 by lumenthi         ###   ########.fr       */
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

static void	main_loop(char **input)
{
	char			*errmsg;
	t_word			*cmd_args;
	t_parse_block	*parsed;
	int				ret;

	errmsg = NULL;
	cmd_args = NULL;
	parsed = NULL;
	exc_mark(input);
	lex_analysis(input, &cmd_args, NULL);
	history_add(*input);
	if (cmd_args)
	{
		//0 = SUCCES;
		//-1 = INVALID;
		//1 = UNFINISHED;
		if ((ret = do_parsing(cmd_args, &parsed, &errmsg)) == 0)
			g_last_command_status = do_interpret(&g_env, parsed);
		else if (ret == 1)
			recursive_main_loop(input);
		else
			g_last_command_status = 1;
		free_parse_block(&parsed);
		delete_wordlist(&cmd_args);
	}
}

void	recursive_main_loop(char **input)
{
	char *tmp;
	char *new;
	char *space;

	space = ft_strjoin(*input, " ");
	tmp = ask_for_input(SLASH_PROMPT);
	new = ft_strjoin(space, tmp);
	free(space);
	free(tmp);
	if (ft_strlen(new) < INPUT_MAX_LEN - 1)
		main_loop(&new);
	else
		ft_putstr_fd("Command too long.\n", 2);
	free(new);
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
