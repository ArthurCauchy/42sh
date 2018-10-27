/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/22 16:53:44 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_env			*g_env = NULL;
t_history	*g_history = NULL;
int			g_with_termcap = 0;
int			g_last_command_status = 0;
t_alias		*g_aliases = NULL;
int			g_winsize_changed = 0;

int			main(int argc, char **argv, char **envp)
{
	char	*errmsg;
	char	*input;
	t_word	*cmd_args;
	t_parse_block *parsed;

	(void)argc;
	(void)argv;
	errmsg = NULL;
	init(&g_env, envp);
	while ((input = ask_for_input(NORMAL_PROMPT)) != NULL)
	{
		cmd_args = NULL;
		exc_mark(&input);
		if (ft_strlen(input) > 0)
		{
			lex_analysis(&input, &cmd_args, NULL);
			history_add(input);
			parsed = do_parsing(cmd_args, &errmsg);
			g_last_command_status = do_interpret(&g_env, parsed);
			free_parse_block(&parsed);
			delete_wordlist(&cmd_args);
		}
		free(input);
	}
	return (0);
}
