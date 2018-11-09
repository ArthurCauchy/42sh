/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:11:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 11:37:28 by acauchy          ###   ########.fr       */
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

// NOTE : the pipeline should always contain at least 1 program
static int	pipeline_run(t_env **cmd_env, t_parse_block *pipeline)
{
	int			child_fds[FD_MAX];
	t_process	*proc;
	int			pl_size;
	int			i;
	pid_t		pgid;
	int			status;
	int			ret;
	t_redirect	*redirs;
	char		*errmsg;

	ft_bzero(child_fds, FD_MAX * sizeof(int));
	pgid = -1;
	pl_size = 0;
	status = 0;
	while (pipeline)
	{
		apply_var_substitution(pipeline->wordlist);
		redirs = NULL;
		handle_pipes(pipeline, &redirs);
		if (analyze_redirects(&pipeline->wordlist, &redirs, &errmsg) == -1)
		{
			print_n_free_errmsg(&errmsg);
			child_fds[pl_size++] = -1;
		}
		else if (pipeline->wordlist == NULL)
		{
			ft_putendl_fd("Invalid null command.", 2);
			child_fds[pl_size++] = -1;
		}
		else
		{
			char **args;
			
			args = arglist_to_array(pipeline->wordlist);
			proc = new_process(cmd_env, args);
			proc->redirs = redirs;
			child_fds[pl_size++] = start_process(cmd_env, proc, pipeline->next || pgid != -1 ? 1 : 0, &pgid);
			delete_process(proc);
		}
		delete_redirects(redirs);
		pipeline = pipeline->next;
	}
	handle_pipes(NULL, NULL);
	i = 0;
	while (i < pl_size)
	{
		if (child_fds[i] <= 0)// IF NOT ONLY A BUILTIN
			ret = -child_fds[i];
		else
		{
			waitpid(child_fds[i], &status, WUNTRACED);
			ret = get_process_return(status);
		}
		++i;
	}
	tcsetpgrp(0, g_shell_pid);
	return (ret);
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
