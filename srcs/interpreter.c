/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 15:09:35 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "utils.h"
#include "builtins.h"
#include "parsing.h"
#include "starter.h"
#include "global.h"
#include "interpreter.h"

static int	pipeline_run(t_env **cmd_env, t_parse_block *pipeline)
{
	t_interpret interpret;
	int			child_fds[FD_MAX];

	ft_bzero(child_fds, FD_MAX * sizeof(int));
	interpret.child_fds = child_fds;
	interpret.pgid = -1;
	interpret.pl_size = 0;
	interpret.status = 0;
	while (pipeline)
	{
		apply_var_substitution(pipeline->wordlist);
		interpret.redirs = NULL;
		handle_pipes(pipeline, &interpret.redirs);
		interpret_loops(&interpret, cmd_env, pipeline);
		delete_redirects(interpret.redirs);
		pipeline = pipeline->next;
	}
	interpret_wait(&interpret);
	return (interpret.ret);
}

static void	pipeline_add(t_parse_block **pipeline, t_parse_block *new)
{
	t_parse_block	*cur;

	cur = *pipeline;
	if (!cur)
	{
		*pipeline = clone_parse_block(new);
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = clone_parse_block(new);
}

int			do_interpret(t_env **cmd_env, t_parse_block *parsed)
{
	int				ret;
	t_parse_block	*pipeline;
	t_parse_block	*cur;

	ret = 0;
	pipeline = NULL;
	cur = parsed;
	while (cur)
	{
		pipeline_add(&pipeline, cur);
		if (cur->separator != PIPE)
		{
			ret = pipeline_run(cmd_env, pipeline);
			free_parse_block(&pipeline);
			if (cur->next && ((ret != 0 && cur->separator == AND)
					|| (ret == 0 && cur->separator == OR)))
				cur = cur->next;
		}
		cur = cur->next;
	}
	free_parse_block(&pipeline);
	return (ret);
}
