/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:00:36 by lumenthi          #+#    #+#             */
/*   Updated: 2018/11/09 15:09:09 by acauchy          ###   ########.fr       */
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

void	handle_end(int *pipefd, char **tmp_str, t_redirect **redirs)
{
	if (pipe(pipefd) == -1)
		exit_error("pipe() error");
	*tmp_str = ft_itoa(pipefd[1]);
	add_redirect(redirs, "1", *tmp_str, PIPE);
	free(*tmp_str);
	*tmp_str = ft_itoa(pipefd[0]);
	add_redirect(redirs, "", *tmp_str, FDCLOSE);
	free(*tmp_str);
}

int		close_fd(int fd)
{
	close(fd);
	return (1);
}

void	handle_pipes(t_parse_block *pipeline, t_redirect **redirs)
{
	char		*tmp_str;
	static int	pipefd[2] = {-1, -1};
	static int	tmp_pipe = -1;

	if (tmp_pipe != -1 && close_fd(tmp_pipe))
		tmp_pipe = -1;
	if (pipefd[1] != -1 && close_fd(pipefd[1]))
		pipefd[1] = -1;
	if (pipefd[0] != -1)
	{
		tmp_str = ft_itoa(pipefd[0]);
		add_redirect(redirs, "0", tmp_str, PIPE);
		free(tmp_str);
		tmp_pipe = pipefd[0];
		pipefd[0] = -1;
	}
	if (pipeline && pipeline->next)
		handle_end(pipefd, &tmp_str, redirs);
}

void	interpret_loops(t_interpret *interpret, t_env **cmd_env,
t_parse_block *pipeline)
{
	char **args;

	if (analyze_redirects(&pipeline->wordlist, &(interpret->redirs),
		&(interpret->errmsg)) == -1)
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
		args = arglist_to_array(pipeline->wordlist);
		interpret->proc = new_process(cmd_env, args);
		interpret->proc->redirs = interpret->redirs;
		interpret->child_fds[interpret->pl_size++] = start_process(cmd_env,
		interpret->proc, pipeline->next ? 1 : 0, &(interpret->pgid));
		delete_process(interpret->proc);
	}
}

void	interpret_wait(t_interpret *interpret)
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
