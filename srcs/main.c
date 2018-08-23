/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/08/23 12:25:35 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "env.h"
#include "builtins.h"
#include "init.h"

t_env		*g_env = NULL;

// TEMPORARY AND UNPROTECTED input loop
static char	*ask_for_input(void)
{
	static char	buff[INPUT_MAX_LEN];
	int			size_read;
	char		*ret;

	ret = NULL;
	ft_putstr("$> ");
	size_read = read(0, buff, INPUT_MAX_LEN);
	if (size_read == -1)
		exit_error("read() error");
	buff[size_read] = '\0';
	if (size_read > 0 && buff[size_read - 1] == '\n')
		buff[size_read - 1] = '\0';
	ret = ft_strdup(buff);
	return (ret);
}

static void	start_command(t_word *cmd_args)
{
	t_builtin	*builtin;
	char		**args;

	args = ft_memalloc(sizeof(char*) * PARAMS_MAX);
	if ((builtin = search_builtin(cmd_args->str)))
	{
		arglist_to_array(cmd_args, args);
		builtin->func(&g_env, args);
		delete_args(args);
	}
	else
		ft_putendl_fd("Not a builtin.", 2);
}

int			main(int argc, char **argv, char **envp)
{
	char	*errmsg;
	char	*input;
	t_word	*cmd_args;

	(void)argc;
	(void)argv;
	errmsg = NULL;
	init(&g_env, envp);
	while ((input = ask_for_input()) != NULL)
	{
		cmd_args = NULL;
		lex_analysis(input, &cmd_args, &errmsg);
		free(input);
		if (errmsg)
			print_n_free_errmsg(&errmsg);
		else
			start_command(cmd_args);
		delete_wordlist(&cmd_args);
	}
	return (0);
}
