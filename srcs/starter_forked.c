/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter_forked.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:35:33 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/08 16:38:45 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "utils.h"
#include "builtins.h"
#include "starter.h"

static void	handle_pgid(pid_t *pgid)
{
	pid_t	pid;

	pid = getpid();
	if (*pgid == -1)
	{
		setpgid(pid, pid);
		tcsetpgrp(0, pid);
	}
	else
		setpgid(pid, *pgid);
}

/*
** When a builtin is in a pipe, then the shell fork,
** the child execute the builtin and returns
*/

int			start_forked_builtin(t_env **cmd_env,
		t_process *proc, t_builtin *builtin, pid_t *pgid)
{
	pid_t	pid;
	char	*errmsg;

	errmsg = NULL;
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	if (pid == 0)
	{
		handle_pgid(pgid);
		reset_sighandlers();
		if (apply_redirects(proc->redirs, NULL, NULL, &errmsg) == -1)
			exit_error(errmsg);
		exit(builtin->func(cmd_env, proc->args));
	}
	if (*pgid == -1)
	{
		*pgid = pid;
		tcsetpgrp(0, pid);
	}
	setpgid(pid, *pgid);
	return (pid);
}

static int	handle_exec_error(char *path, char **args)
{
	if (path && is_there_a_file(path))
	{
		if (is_directory(path))
			ft_fminiprint(2, "%l0s%: Is a directory.\n", path);
		else if (!is_executable(path))
			ft_fminiprint(2, "%l0s%: Permission denied.\n", path);
		else
			return (0);
		return (126);
	}
	else
	{
		if (args[0])
			ft_fminiprint(2, "%l0s%: Command not found.\n", args[0]);
		else
			ft_fminiprint(2, "Command not found.\n");
		return (127);
	}
}

int			start_external_process(t_env **cmd_env,
		t_process *proc, pid_t *pgid)
{
	char	*errmsg;
	pid_t	pid;
	int		errcode;

	errmsg = NULL;
	if ((errcode = handle_exec_error(proc->path, proc->args)) != 0)
		return (-errcode);
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	if (pid == 0)
	{
		handle_pgid(pgid);
		reset_sighandlers();
		if (apply_redirects(proc->redirs, NULL, NULL, &errmsg) == -1)
			exit_error(errmsg);
		execve(proc->path, proc->args, env_to_array(cmd_env));
		exit_error("execve() error");
	}
	if (*pgid == -1)
	{
		*pgid = pid;
		tcsetpgrp(0, pid);
	}
	setpgid(pid, *pgid);
	return (pid);
}
