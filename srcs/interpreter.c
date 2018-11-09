/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 14:10:53 by lumenthi         ###   ########.fr       */
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

static void	handle_pipes(t_parse_block *pipeline, t_redirect **redirs)
{
	char		*tmp_str;
	static int	pipefd[2] = {-1, -1};
	static int	tmp_pipe = -1;

	if (tmp_pipe != -1)
	{
		close(tmp_pipe);
		tmp_pipe = -1;
	}
	if (pipefd[1] != -1)
	{
		close(pipefd[1]);
		pipefd[1] = -1;
	}
	if (pipefd[0] != -1)
	{
		tmp_str = ft_itoa(pipefd[0]);
		add_redirect(redirs, "0", tmp_str, PIPE);
		free(tmp_str);
		tmp_pipe = pipefd[0];
		pipefd[0] = -1;
	}
	if (pipeline && pipeline->next)
	{
		if (pipe(pipefd) == -1)
			exit_error("pipe() error");
		tmp_str = ft_itoa(pipefd[1]);
		add_redirect(redirs, "1", tmp_str, PIPE);
		free(tmp_str);
		tmp_str = ft_itoa(pipefd[0]);
		add_redirect(redirs, "", tmp_str, FDCLOSE);
		free(tmp_str);
	}
}

static void	interpret_loops(t_interpret *interpret, t_env **cmd_env, t_parse_block *pipeline)
{
	char **args;

	if (analyze_redirects(&pipeline->wordlist, &(interpret->redirs), &(interpret->errmsg)) == -1)
	{
		print_n_free_errmsg(&(interpret->errmsg));
		interpret->child_fds[interpret->pl_size++] = -1;
	}
	else if (pipeline->wordlist == NULL)
	{
		ft_putendl_fd("Invalid null command.", 2);
		interpret->child_fds[interpret->pl_size++] = -1;
	}
	else
	{
		apply_var_substitution(pipeline->wordlist);
		args = arglist_to_array(pipeline->wordlist);
		interpret->proc = new_process(cmd_env, args);
		interpret->proc->redirs = interpret->redirs;
		interpret->child_fds[interpret->pl_size++] = start_process(cmd_env, interpret->proc, pipeline->next ? 1 : 0, &(interpret->pgid));
		delete_process(interpret->proc);
	}
}

static void	interpret_wait(t_interpret *interpret)
{
	int i;

	i = 0;
	handle_pipes(NULL, NULL);
	while (i < interpret->pl_size)
	{
		if (interpret->child_fds[i] <= 0)
			interpret->ret = -interpret->child_fds[i];
		else
		{
			waitpid(interpret->child_fds[i], &(interpret->status), WUNTRACED);
			interpret->ret = get_process_return(interpret->status);
		}
		++i;
	}
	tcsetpgrp(0, g_shell_pid);
}

static int	pipeline_run(t_env **cmd_env, t_parse_block *pipeline)
{
	t_interpret interpret;

	ft_bzero(interpret.child_fds, FD_MAX * sizeof(int));
	interpret.pgid = -1;
	interpret.pl_size = 0;
	interpret.status = 0;
	while (pipeline)
	{
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
		return;
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
