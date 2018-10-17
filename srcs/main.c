/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/17 14:10:11 by saxiao           ###   ########.fr       */
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

t_env			*g_env = NULL;
t_history	*g_history = NULL;
int			g_with_termcap = 0;

static void	start_command(t_word *cmd_args)
{
	t_builtin	*builtin;
	char		**args;

	args = ft_memalloc(sizeof(char*) * PARAMS_MAX);
	if ((builtin = search_builtin(cmd_args->str)))
	{
		arglist_to_array(cmd_args, args);
		builtin->func(&g_env, args);
	}
	else
		ft_putendl_fd("Not a builtin.", 2);
	delete_args(args);
}
#include <stdio.h>
int			main(int argc, char **argv, char **envp)
{
	char	*errmsg;
	char	*input;
	t_word	*cmd_args;

	(void)argc;
	(void)argv;
	errmsg = NULL;
	init(&g_env, envp);
	while ((input = ask_for_input("$> ")) != NULL)
	{
		printf("%s\n", input);
		cmd_args = NULL;
		exc_mark(&input);
		if (ft_strlen(input) > 0)
		{
			lex_analysis(&input, &cmd_args, &errmsg);
			history_add(input);
			if (errmsg)
				print_n_free_errmsg(&errmsg);
			else
				start_command(cmd_args);
			delete_wordlist(&cmd_args);
		}
		free(input);
	}
	return (0);
}
