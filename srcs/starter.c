/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:35:33 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 14:08:42 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "libft.h"
#include "env.h"
#include "utils.h"
#include "builtins.h"
#include "starter.h"
#include "global.h"

int			start_builtin(t_process *proc, t_builtin *builtin)
{
	int			ret;
	char		*errmsg;
	int			fdtmp_array[FD_MAX];
	int			fdsave_array[FD_MAX];

	errmsg = NULL;
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

/*
** Starts a process and returns it's pid
** Params :
** - cmd_env : local env of the command
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
	t_builtin	*builtin;

	if ((builtin = search_builtin(proc->args[0])))
	{
		if (!forked)
			return (start_builtin(proc, builtin));
		else
			return (start_forked_builtin(cmd_env, proc, builtin, pgid));
	}
	return (start_external_process(cmd_env, proc, pgid));
}
