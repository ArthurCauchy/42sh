/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:35:33 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/08 13:08:05 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "env.h"
#include "utils.h"
#include "builtins.h"
#include "starter.h"
#include "global.h"

/*
** When a builtin is in a pipe, then the shell fork,
** the child execute the builtin and returns
*/

static int	start_forked_builtin(t_env **cmd_env,
		t_process *proc, t_builtin *builtin, pid_t *pgid)
{
	pid_t	pid;
	char	*errmsg;

	errmsg = NULL;
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	if (pid == 0)
	{
		pid = getpid();
		if (*pgid == -1)
		{
			setpgid(pid, pid);
			tcsetpgrp(0, pid);
		}
		else
			setpgid(pid, *pgid);
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

static int	start_external_process(t_env **cmd_env,
		t_process *proc, pid_t *pgid)
{
	char	*errmsg;
	pid_t	pid;
	int		errcode;

	errmsg = NULL;
	errcode = handle_exec_error(proc->path, proc->args);
	if (errcode != 0)
		return (-errcode);
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	if (pid == 0)
	{
		pid = getpid();
		if (*pgid == -1)
		{
			setpgid(pid, pid);
			tcsetpgrp(0, pid);
		}
		else
			setpgid(pid, *pgid);
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

/*
** Starts a process and returns it's pid
** Params :
** - proc : process to start
** - forked : start command in new process ? 1:yes/0:no
** - pgid : the Process Group ID of the new process.
**          -1 if it should create it's own
** Return:
** - (n>0) the new process pid
** - (n<=0) error code or builtin's exit status
**
** If the process creates it's own pgid, the value of the pgid pointer is set
*/

int			start_process(t_env **cmd_env,
		t_process *proc, int forked, pid_t *pgid)
{
	int			ret;
	t_builtin	*builtin;
	static int	fdtmp_array[FD_MAX];
	static int	fdsave_array[FD_MAX];
	char		*errmsg;

	errmsg = NULL;
	if ((builtin = search_builtin(proc->args[0])))
	{
		if (!forked)
		{
			ft_bzero(fdtmp_array, FD_MAX * sizeof(int));
			ft_memset(fdsave_array, -1, FD_MAX * sizeof(int));
			if (apply_redirects(proc->redirs, fdtmp_array,
						fdsave_array, &errmsg) == -1)
			{
				print_n_free_errmsg(&errmsg);
				restore_filedes(fdtmp_array, fdsave_array);
				return (-1);
			}
			ret = -builtin->func(&g_env, proc->args);
			restore_filedes(fdtmp_array, fdsave_array);
			return (ret);
		}
		else
			return (start_forked_builtin(cmd_env, proc, builtin, pgid));
	}
	return (start_external_process(cmd_env, proc, pgid));
}
