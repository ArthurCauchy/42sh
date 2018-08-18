/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_procs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:30:41 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/19 16:03:53 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	print_procs(void)
{
	t_process	*cur;
	int			pid;
	int			pgid;

	cur = g_shell.saved_processes;
	while (cur)
	{
		pid = cur->pid;
		if ((pgid = getpgid(pid)) == -1)
			ft_fminiprint(1, "%l12s% %l0s%\n", "TERMINATED", cur->args[0]);
		else
			ft_fminiprint(1, "%l6d% %l6d% %l0s%\n", &pid, &pgid, cur->args[0]);
		cur = cur->next;
	}
}

int			builtin_procs(t_env **env, char **args)
{
	(void)env;
	if (args[1])
	{
		ft_putendl_fd("procs: Too many arguments.", 2);
		return (1);
	}
	if (!g_shell.saved_processes)
	{
		ft_putendl_fd("No stopped process.", 2);
		return (1);
	}
	ft_fminiprint(1, "%l6s% %l6s% %l0s%\n", "PID", "PGID", "NAME");
	print_procs();
	return (0);
}
