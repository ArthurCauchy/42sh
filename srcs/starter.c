/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:35:33 by acauchy           #+#    #+#             */
/*   Updated: 2018/10/22 12:35:17 by acauchy          ###   ########.fr       */
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
** When a builtin is in a pipe, then the shell fork, the child execute the builtin and returns
*/
static int	start_forked_builtin(t_process *proc, t_builtin *builtin)
{
	pid_t	pid;
	char	*errmsg;

	errmsg = NULL;
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	if (pid == 0)
	{
		if (apply_redirects(proc->redirs, NULL, NULL, &errmsg) == -1)
			exit_error(errmsg);
		exit(builtin->func(&g_env, proc->args));
	}
	return (pid);
}

static int	start_external_process(t_process *proc)
{
	char	*errmsg;
	pid_t	pid;

	errmsg = NULL;
	if (!proc->path || !is_there_a_file(proc->path)
			|| !is_executable(proc->path)) // TODO print error msg based on error type
	{
		ft_putendl_fd("Command not found.", 2);
		return (-127);
	}
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	if (pid == 0)
	{
		if (apply_redirects(proc->redirs, NULL, NULL, &errmsg) == -1)
			exit_error(errmsg);
		execve(proc->path, proc->args, env_to_array(&g_env)); // TODO change to command env
		exit_error("execve() error");
	}
	return (pid);
}

/*
** Starts a process and returns it's pid
** Params :
** - proc : process to start
** - forked : start command in new process ? 1:yes/0:no
** Return:
** - (n>0) the new process pid
** - (n<0) error code or builtin's exit status
*/
int			start_process(t_process *proc, int forked)
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
			if (apply_redirects(proc->redirs, fdtmp_array, fdsave_array, &errmsg) == -1)
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
			return (start_forked_builtin(proc, builtin));
	}
	return (start_external_process(proc));
}
